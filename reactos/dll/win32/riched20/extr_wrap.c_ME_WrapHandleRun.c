#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_14__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ x; int /*<<< orphan*/  y; } ;
struct TYPE_34__ {int len; int nFlags; scalar_t__ nWidth; TYPE_1__ pt; } ;
struct TYPE_30__ {TYPE_8__ run; } ;
struct TYPE_35__ {scalar_t__ type; struct TYPE_35__* next; TYPE_4__ member; } ;
struct TYPE_32__ {scalar_t__ x; int /*<<< orphan*/  y; } ;
struct TYPE_33__ {scalar_t__ nAvailWidth; TYPE_6__ pt; TYPE_9__* pLastSplittableRun; TYPE_9__* pRowStart; void* bOverflown; TYPE_14__* context; scalar_t__ bWordWrap; int /*<<< orphan*/  nFirstMargin; int /*<<< orphan*/  nLeftMargin; scalar_t__ nRow; TYPE_3__* pPara; } ;
struct TYPE_31__ {scalar_t__ x; } ;
struct TYPE_28__ {int /*<<< orphan*/  para; } ;
struct TYPE_29__ {TYPE_2__ member; } ;
struct TYPE_26__ {TYPE_5__ pt; } ;
typedef  TYPE_7__ ME_WrapContext ;
typedef  TYPE_8__ ME_Run ;
typedef  TYPE_9__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 void* FALSE ; 
 int MERF_ENDPARA ; 
 int MERF_ENDROW ; 
 int MERF_ENDWHITE ; 
 int MERF_GRAPHICS ; 
 int MERF_SPLITTABLE ; 
 int MERF_STARTWHITE ; 
 int MERF_TAB ; 
 int MERF_WHITESPACE ; 
 int /*<<< orphan*/  ME_InsertRowStart (TYPE_7__*,TYPE_9__*) ; 
 TYPE_9__* ME_SplitByBacktracking (TYPE_7__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  ME_WrapSizeRun (TYPE_7__*,TYPE_9__*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  calc_run_extent (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ diRun ; 
 int find_non_whitespace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int reverse_find_non_whitespace (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* split_run_extents (TYPE_7__*,TYPE_9__*,int) ; 

__attribute__((used)) static ME_DisplayItem *ME_WrapHandleRun(ME_WrapContext *wc, ME_DisplayItem *p)
{
  ME_DisplayItem *pp;
  ME_Run *run;
  int len;

  assert(p->type == diRun);
  if (!wc->pRowStart)
    wc->pRowStart = p;
  run = &p->member.run;
  run->pt.x = wc->pt.x;
  run->pt.y = wc->pt.y;
  ME_WrapSizeRun(wc, p);
  len = run->len;

  if (wc->bOverflown) /* just skipping final whitespaces */
  {
    /* End paragraph run can't overflow to the next line by itself. */
    if (run->nFlags & MERF_ENDPARA)
      return p->next;

    if (run->nFlags & MERF_WHITESPACE) {
      wc->pt.x += run->nWidth;
      /* skip runs consisting of only whitespaces */
      return p->next;
    }

    if (run->nFlags & MERF_STARTWHITE) {
      /* try to split the run at the first non-white char */
      int black;
      black = find_non_whitespace( get_text( run, 0 ), run->len, 0 );
      if (black) {
        wc->bOverflown = FALSE;
        pp = split_run_extents(wc, p, black);
        calc_run_extent(wc->context, &wc->pPara->member.para,
                        wc->nRow ? wc->nLeftMargin : wc->nFirstMargin,
                        &pp->member.run);
        ME_InsertRowStart(wc, pp);
        return pp;
      }
    }
    /* black run: the row goes from pRowStart to the previous run */
    ME_InsertRowStart(wc, p);
    return p;
  }
  /* simply end the current row and move on to next one */
  if (run->nFlags & MERF_ENDROW)
  {
    p = p->next;
    ME_InsertRowStart(wc, p);
    return p;
  }

  /* will current run fit? */
  if (wc->bWordWrap &&
      wc->pt.x + run->nWidth - wc->context->pt.x > wc->nAvailWidth)
  {
    int loc = wc->context->pt.x + wc->nAvailWidth - wc->pt.x;
    /* total white run or end para */
    if (run->nFlags & (MERF_WHITESPACE | MERF_ENDPARA)) {
      /* let the overflow logic handle it */
      wc->bOverflown = TRUE;
      return p;
    }
    /* TAB: we can split before */
    if (run->nFlags & MERF_TAB) {
      wc->bOverflown = TRUE;
      if (wc->pRowStart == p)
        /* Don't split before the start of the run, or we will get an
         * endless loop. */
        return p->next;
      else
        return p;
    }
    /* graphics: we can split before, if run's width is smaller than row's width */
    if ((run->nFlags & MERF_GRAPHICS) && run->nWidth <= wc->nAvailWidth) {
      wc->bOverflown = TRUE;
      return p;
    }
    /* can we separate out the last spaces ? (to use overflow logic later) */
    if (run->nFlags & MERF_ENDWHITE)
    {
      /* we aren't sure if it's *really* necessary, it's a good start however */
      int black = reverse_find_non_whitespace( get_text( run, 0 ), len );
      split_run_extents(wc, p, black);
      /* handle both parts again */
      return p;
    }
    /* determine the split point by backtracking */
    pp = ME_SplitByBacktracking(wc, p, loc);
    if (pp == wc->pRowStart)
    {
      if (run->nFlags & MERF_STARTWHITE)
      {
          /* We had only spaces so far, so we must be on the first line of the
           * paragraph (or the first line after MERF_ENDROW forced the line
           * break within the paragraph), since no other lines of the paragraph
           * start with spaces. */

          /* The lines will only contain spaces, and the rest of the run will
           * overflow onto the next line. */
          wc->bOverflown = TRUE;
          return p;
      }
      /* Couldn't split the first run, possible because we have a large font
       * with a single character that caused an overflow.
       */
      wc->pt.x += run->nWidth;
      return p->next;
    }
    if (p != pp) /* found a suitable split point */
    {
      wc->bOverflown = TRUE;
      return pp;
    }
    /* we detected that it's best to split on start of this run */
    if (wc->bOverflown)
      return pp;
    ERR("failure!\n");
    /* not found anything - writing over margins is the only option left */
  }
  if ((run->nFlags & (MERF_SPLITTABLE | MERF_STARTWHITE))
    || ((run->nFlags & (MERF_GRAPHICS|MERF_TAB)) && (p != wc->pRowStart)))
  {
    wc->pLastSplittableRun = p;
  }
  wc->pt.x += run->nWidth;
  return p->next;
}