#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_5__* pRun; void* pPara; scalar_t__ nOffset; } ;
struct TYPE_14__ {int x; } ;
struct TYPE_12__ {int nWidth; int nFlags; TYPE_2__ pt; } ;
struct TYPE_13__ {int x; } ;
struct TYPE_16__ {TYPE_1__ pt; } ;
struct TYPE_15__ {TYPE_11__ run; TYPE_4__ row; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_3__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_Row ;
typedef  TYPE_5__ ME_DisplayItem ;
typedef  TYPE_6__ ME_Cursor ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MERF_ENDPARA ; 
 scalar_t__ ME_CharFromPoint (int /*<<< orphan*/ *,int,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ME_FindItemFwd (TYPE_5__*,scalar_t__) ; 
 void* ME_GetParagraph (TYPE_5__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diRun ; 
 scalar_t__ diRunOrStartRow ; 

__attribute__((used)) static BOOL ME_FindRunInRow(ME_TextEditor *editor, ME_DisplayItem *pRow,
                            int x, ME_Cursor *cursor, BOOL *pbCaretAtEnd)
{
  ME_DisplayItem *pNext, *pLastRun;
  ME_Row *row = &pRow->member.row;
  BOOL exact = TRUE;

  if (x < row->pt.x)
  {
      x = row->pt.x;
      exact = FALSE;
  }
  pNext = ME_FindItemFwd(pRow, diRunOrStartRow);
  assert(pNext->type == diRun);
  if (pbCaretAtEnd) *pbCaretAtEnd = FALSE;
  cursor->nOffset = 0;
  do {
    int run_x = pNext->member.run.pt.x;
    int width = pNext->member.run.nWidth;

    if (x >= run_x && x < run_x+width)
    {
      cursor->nOffset = ME_CharFromPoint(editor, x-run_x, &pNext->member.run, TRUE, TRUE);
      cursor->pRun = pNext;
      cursor->pPara = ME_GetParagraph( cursor->pRun );
      return exact;
    }
    pLastRun = pNext;
    pNext = ME_FindItemFwd(pNext, diRunOrStartRow);
  } while(pNext && pNext->type == diRun);

  if ((pLastRun->member.run.nFlags & MERF_ENDPARA) == 0)
  {
    cursor->pRun = ME_FindItemFwd(pNext, diRun);
    if (pbCaretAtEnd) *pbCaretAtEnd = TRUE;
  }
  else
    cursor->pRun = pLastRun;

  cursor->pPara = ME_GetParagraph( cursor->pRun );
  return FALSE;
}