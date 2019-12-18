#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int dwMask; int wEffects; } ;
struct TYPE_14__ {TYPE_6__ fmt; } ;
struct TYPE_15__ {TYPE_2__ para; } ;
struct TYPE_20__ {TYPE_3__ member; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; } ;
struct TYPE_19__ {TYPE_1__ pt; TYPE_5__* context; scalar_t__ pRowStart; TYPE_8__* pPara; } ;
struct TYPE_17__ {TYPE_4__* editor; } ;
struct TYPE_16__ {scalar_t__ bEmulateVersion10; } ;
typedef  TYPE_6__ PARAFORMAT2 ;
typedef  TYPE_7__ ME_WrapContext ;
typedef  TYPE_8__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_InsertRowStart (TYPE_7__*,TYPE_8__*) ; 
 int PFE_TABLE ; 
 int PFM_TABLE ; 

__attribute__((used)) static void ME_WrapEndParagraph(ME_WrapContext *wc, ME_DisplayItem *p)
{
  ME_DisplayItem *para = wc->pPara;
  PARAFORMAT2 *pFmt = &para->member.para.fmt;
  if (wc->pRowStart)
    ME_InsertRowStart(wc, p);
  if (wc->context->editor->bEmulateVersion10 && /* v1.0 - 3.0 */
      pFmt->dwMask & PFM_TABLE && pFmt->wEffects & PFE_TABLE)
  {
    /* ME_BeginRow was called an extra time for the paragraph, and it shifts the
     * text down by one pixel for the border, so fix up the wrap context. */
    wc->pt.y--;
  }

  /*
  p = para->next;
  while(p) {
    if (p->type == diParagraph || p->type == diTextEnd)
      return;
    if (p->type == diRun)
    {
      ME_Run *run = &p->member.run;
      TRACE("%s - (%d, %d)\n", debugstr_run(run), run->pt.x, run->pt.y);
    }
    p = p->next;
  }
  */
}