#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int len; int nFlags; } ;
struct TYPE_14__ {int nOffset; TYPE_3__* pRun; TYPE_3__* pPara; } ;
struct TYPE_11__ {int nFlags; TYPE_3__* next_para; TYPE_3__* prev_para; } ;
struct TYPE_12__ {TYPE_1__ para; TYPE_5__ run; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_3__ ME_DisplayItem ;
typedef  TYPE_4__ ME_Cursor ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int MEPF_ROWSTART ; 
 int MERF_ENDPARA ; 
 void* ME_CallWordBreakProc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* ME_FindItemBack (TYPE_3__*,scalar_t__) ; 
 TYPE_3__* ME_FindItemFwd (TYPE_3__*,scalar_t__) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WB_ISDELIMITER ; 
 int /*<<< orphan*/  WB_MOVEWORDLEFT ; 
 int /*<<< orphan*/  WB_MOVEWORDRIGHT ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 
 scalar_t__ diRunOrParagraph ; 
 scalar_t__ diRunOrParagraphOrEnd ; 
 scalar_t__ diTextStart ; 
 int /*<<< orphan*/  get_text (TYPE_5__*,int /*<<< orphan*/ ) ; 

BOOL
ME_MoveCursorWords(ME_TextEditor *editor, ME_Cursor *cursor, int nRelOfs)
{
  ME_DisplayItem *pRun = cursor->pRun, *pOtherRun;
  ME_DisplayItem *pPara = cursor->pPara;
  int nOffset = cursor->nOffset;

  if (nRelOfs == -1)
  {
    /* Backward movement */
    while (TRUE)
    {
      nOffset = ME_CallWordBreakProc(editor, get_text( &pRun->member.run, 0 ),
                                     pRun->member.run.len, nOffset, WB_MOVEWORDLEFT);
      if (nOffset)
        break;
      pOtherRun = ME_FindItemBack(pRun, diRunOrParagraph);
      if (pOtherRun->type == diRun)
      {
        if (ME_CallWordBreakProc(editor, get_text( &pOtherRun->member.run, 0 ),
                                 pOtherRun->member.run.len,
                                 pOtherRun->member.run.len - 1,
                                 WB_ISDELIMITER)
            && !(pRun->member.run.nFlags & MERF_ENDPARA)
            && !(cursor->pRun == pRun && cursor->nOffset == 0)
            && !ME_CallWordBreakProc(editor, get_text( &pRun->member.run, 0 ),
                                     pRun->member.run.len, 0,
                                     WB_ISDELIMITER))
          break;
        pRun = pOtherRun;
        nOffset = pOtherRun->member.run.len;
      }
      else if (pOtherRun->type == diParagraph)
      {
        if (cursor->pRun == pRun && cursor->nOffset == 0)
        {
          pPara = pOtherRun;
          /* Skip empty start of table row paragraph */
          if (pPara->member.para.prev_para->member.para.nFlags & MEPF_ROWSTART)
            pPara = pPara->member.para.prev_para;
          /* Paragraph breaks are treated as separate words */
          if (pPara->member.para.prev_para->type == diTextStart)
            return FALSE;

          pRun = ME_FindItemBack(pPara, diRun);
          pPara = pPara->member.para.prev_para;
        }
        break;
      }
    }
  }
  else
  {
    /* Forward movement */
    BOOL last_delim = FALSE;
    
    while (TRUE)
    {
      if (last_delim && !ME_CallWordBreakProc(editor, get_text( &pRun->member.run, 0 ),
                                              pRun->member.run.len, nOffset, WB_ISDELIMITER))
        break;
      nOffset = ME_CallWordBreakProc(editor, get_text( &pRun->member.run, 0 ),
                                     pRun->member.run.len, nOffset, WB_MOVEWORDRIGHT);
      if (nOffset < pRun->member.run.len)
        break;
      pOtherRun = ME_FindItemFwd(pRun, diRunOrParagraphOrEnd);
      if (pOtherRun->type == diRun)
      {
        last_delim = ME_CallWordBreakProc(editor, get_text( &pRun->member.run, 0 ),
                                          pRun->member.run.len, nOffset - 1, WB_ISDELIMITER);
        pRun = pOtherRun;
        nOffset = 0;
      }
      else if (pOtherRun->type == diParagraph)
      {
        if (pOtherRun->member.para.nFlags & MEPF_ROWSTART)
            pOtherRun = pOtherRun->member.para.next_para;
        if (cursor->pRun == pRun) {
          pPara = pOtherRun;
          pRun = ME_FindItemFwd(pPara, diRun);
        }
        nOffset = 0;
        break;
      }
      else /* diTextEnd */
      {
        if (cursor->pRun == pRun)
          return FALSE;
        nOffset = 0;
        break;
      }
    }
  }
  cursor->pPara = pPara;
  cursor->pRun = pRun;
  cursor->nOffset = nOffset;
  return TRUE;
}