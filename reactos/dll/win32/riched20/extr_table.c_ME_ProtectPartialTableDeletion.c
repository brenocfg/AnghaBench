#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;

/* Type definitions */
struct TYPE_30__ {int nOffset; TYPE_8__* pRun; TYPE_8__* pPara; } ;
struct TYPE_28__ {int nFlags; int nCharOfs; int len; } ;
struct TYPE_24__ {int dwMask; int wEffects; } ;
struct TYPE_25__ {int nCharOfs; scalar_t__ pCell; int nFlags; TYPE_8__* prev_para; TYPE_3__ fmt; TYPE_8__* next_para; } ;
struct TYPE_26__ {TYPE_7__ run; TYPE_4__ para; } ;
struct TYPE_29__ {TYPE_5__ member; } ;
struct TYPE_27__ {int /*<<< orphan*/  bEmulateVersion10; } ;
struct TYPE_22__ {TYPE_8__* next_para; } ;
struct TYPE_23__ {TYPE_1__ para; } ;
struct TYPE_21__ {TYPE_2__ member; } ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  TYPE_7__ ME_Run ;
typedef  TYPE_8__ ME_DisplayItem ;
typedef  TYPE_9__ ME_Cursor ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 int MERF_ENDPARA ; 
 int MERF_TAB ; 
 TYPE_8__* ME_FindItemBack (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ME_FindItemFwd (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int ME_GetCursorOfs (TYPE_9__*) ; 
 TYPE_14__* ME_GetTableRowEnd (TYPE_8__*) ; 
 int /*<<< orphan*/  ME_MoveCursorChars (TYPE_6__*,TYPE_9__*,int,scalar_t__) ; 
 int PFE_TABLE ; 
 int PFM_TABLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  diRun ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

void ME_ProtectPartialTableDeletion(ME_TextEditor *editor, ME_Cursor *c, int *nChars)
{
  int nOfs = ME_GetCursorOfs(c);
  ME_Cursor c2 = *c;
  ME_DisplayItem *this_para = c->pPara;
  ME_DisplayItem *end_para;

  ME_MoveCursorChars(editor, &c2, *nChars, FALSE);
  end_para = c2.pPara;
  if (c2.pRun->member.run.nFlags & MERF_ENDPARA) {
    /* End offset might be in the middle of the end paragraph run.
     * If this is the case, then we need to use the next paragraph as the last
     * paragraphs.
     */
    int remaining = nOfs + *nChars - c2.pRun->member.run.nCharOfs
                    - end_para->member.para.nCharOfs;
    if (remaining)
    {
      assert(remaining < c2.pRun->member.run.len);
      end_para = end_para->member.para.next_para;
    }
  }
  if (!editor->bEmulateVersion10) { /* v4.1 */
    if (this_para->member.para.pCell != end_para->member.para.pCell ||
        ((this_para->member.para.nFlags|end_para->member.para.nFlags)
         & (MEPF_ROWSTART|MEPF_ROWEND)))
    {
      while (this_para != end_para)
      {
        ME_DisplayItem *next_para = this_para->member.para.next_para;
        BOOL bTruancateDeletion = FALSE;
        if (this_para->member.para.nFlags & MEPF_ROWSTART) {
          /* The following while loop assumes that next_para is MEPF_ROWSTART,
           * so moving back one paragraph let's it be processed as the start
           * of the row. */
          next_para = this_para;
          this_para = this_para->member.para.prev_para;
        } else if (next_para->member.para.pCell != this_para->member.para.pCell
                   || this_para->member.para.nFlags & MEPF_ROWEND)
        {
          /* Start of the deletion from after the start of the table row. */
          bTruancateDeletion = TRUE;
        }
        while (!bTruancateDeletion &&
               next_para->member.para.nFlags & MEPF_ROWSTART)
        {
          next_para = ME_GetTableRowEnd(next_para)->member.para.next_para;
          if (next_para->member.para.nCharOfs > nOfs + *nChars)
          {
            /* End of deletion is not past the end of the table row. */
            next_para = this_para->member.para.next_para;
            /* Delete the end paragraph preceding the table row if the
             * preceding table row will be empty. */
            if (this_para->member.para.nCharOfs >= nOfs)
            {
              next_para = next_para->member.para.next_para;
            }
            bTruancateDeletion = TRUE;
          } else {
            this_para = next_para->member.para.prev_para;
          }
        }
        if (bTruancateDeletion)
        {
          ME_Run *end_run = &ME_FindItemBack(next_para, diRun)->member.run;
          int nCharsNew = (next_para->member.para.nCharOfs - nOfs
                           - end_run->len);
          nCharsNew = max(nCharsNew, 0);
          assert(nCharsNew <= *nChars);
          *nChars = nCharsNew;
          break;
        }
        this_para = next_para;
      }
    }
  } else { /* v1.0 - 3.0 */
    ME_DisplayItem *pRun;
    int nCharsToBoundary;

    if ((this_para->member.para.nCharOfs != nOfs || this_para == end_para) &&
        this_para->member.para.fmt.dwMask & PFM_TABLE &&
        this_para->member.para.fmt.wEffects & PFE_TABLE)
    {
      pRun = c->pRun;
      /* Find the next tab or end paragraph to use as a delete boundary */
      while (!(pRun->member.run.nFlags & (MERF_TAB|MERF_ENDPARA)))
        pRun = ME_FindItemFwd(pRun, diRun);
      nCharsToBoundary = pRun->member.run.nCharOfs
                         - c->pRun->member.run.nCharOfs
                         - c->nOffset;
      *nChars = min(*nChars, nCharsToBoundary);
    } else if (end_para->member.para.fmt.dwMask & PFM_TABLE &&
               end_para->member.para.fmt.wEffects & PFE_TABLE)
    {
      /* The deletion starts from before the row, so don't join it with
       * previous non-empty paragraphs. */
      ME_DisplayItem *curPara;
      pRun = NULL;
      if (nOfs > this_para->member.para.nCharOfs) {
        pRun = ME_FindItemBack(end_para, diRun);
        curPara = end_para->member.para.prev_para;
      }
      if (!pRun) {
        pRun = ME_FindItemFwd(end_para, diRun);
        curPara = end_para;
      }
      if (pRun)
      {
        nCharsToBoundary = curPara->member.para.nCharOfs
                           + pRun->member.run.nCharOfs
                           - nOfs;
        if (nCharsToBoundary >= 0)
          *nChars = min(*nChars, nCharsToBoundary);
      }
    }
    if (*nChars < 0)
      *nChars = 0;
  }
}