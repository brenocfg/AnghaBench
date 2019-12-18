#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_34__ {int y; } ;
struct TYPE_35__ {int nHeight; TYPE_7__ pt; } ;
struct TYPE_32__ {int y; } ;
struct TYPE_33__ {int nHeight; int nFlags; TYPE_5__ pt; TYPE_12__* next_para; } ;
struct TYPE_36__ {TYPE_8__ row; TYPE_6__ para; } ;
struct TYPE_31__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_28__ {TYPE_12__* next_para; } ;
struct TYPE_29__ {TYPE_1__ para; } ;
struct TYPE_30__ {TYPE_2__ member; } ;
struct TYPE_27__ {scalar_t__ type; TYPE_9__ member; } ;
struct TYPE_26__ {TYPE_10__* pBuffer; TYPE_4__ rcFormat; } ;
struct TYPE_25__ {TYPE_12__* pLast; TYPE_3__* pFirst; } ;
typedef  TYPE_11__ ME_TextEditor ;
typedef  TYPE_12__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int MEPF_ROWSTART ; 
 TYPE_12__* ME_FindItemBack (TYPE_12__*,scalar_t__) ; 
 TYPE_12__* ME_FindItemFwd (TYPE_12__*,scalar_t__) ; 
 TYPE_12__* ME_FindPixelPosInTableRow (int,int,TYPE_12__*) ; 
 scalar_t__ ME_FindRunInRow (TYPE_11__*,TYPE_12__*,int,int /*<<< orphan*/ *,int*) ; 
 TYPE_12__* ME_GetTableRowEnd (TYPE_12__*) ; 
 int /*<<< orphan*/  ME_SetCursorToEnd (TYPE_11__*,int /*<<< orphan*/ *,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diStartRow ; 

__attribute__((used)) static BOOL ME_FindPixelPos(ME_TextEditor *editor, int x, int y,
                            ME_Cursor *result, BOOL *is_eol, BOOL final_eop)
{
  ME_DisplayItem *p = editor->pBuffer->pFirst->member.para.next_para;
  BOOL isExact = TRUE;

  x -= editor->rcFormat.left;
  y -= editor->rcFormat.top;

  if (is_eol)
    *is_eol = FALSE;

  /* find paragraph */
  for (; p != editor->pBuffer->pLast; p = p->member.para.next_para)
  {
    assert(p->type == diParagraph);
    if (y < p->member.para.pt.y + p->member.para.nHeight)
    {
      if (p->member.para.nFlags & MEPF_ROWSTART)
        p = ME_FindPixelPosInTableRow(x, y, p);
      y -= p->member.para.pt.y;
      p = ME_FindItemFwd(p, diStartRow);
      break;
    } else if (p->member.para.nFlags & MEPF_ROWSTART) {
      p = ME_GetTableRowEnd(p);
    }
  }
  /* find row */
  for (; p != editor->pBuffer->pLast; )
  {
    ME_DisplayItem *pp;
    assert(p->type == diStartRow);
    if (y < p->member.row.pt.y + p->member.row.nHeight) break;
    pp = ME_FindItemFwd(p, diStartRow);
    if (!pp) break;
    p = pp;
  }
  if (p == editor->pBuffer->pLast && !final_eop)
  {
    /* The position is below the last paragraph, so the last row will be used
     * rather than the end of the text, so the x position will be used to
     * determine the offset closest to the pixel position. */
    isExact = FALSE;
    p = ME_FindItemBack(p, diStartRow);
    if (!p) p = editor->pBuffer->pLast;
  }

  assert( p->type == diStartRow || p == editor->pBuffer->pLast );

  if( p->type == diStartRow )
      return ME_FindRunInRow( editor, p, x, result, is_eol ) && isExact;

  ME_SetCursorToEnd(editor, result, TRUE);
  return FALSE;
}