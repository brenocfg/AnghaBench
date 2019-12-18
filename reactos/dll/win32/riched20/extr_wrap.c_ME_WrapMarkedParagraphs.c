#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {int y; scalar_t__ x; } ;
struct TYPE_31__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_38__ {TYPE_5__ pt; TYPE_2__ rcView; } ;
struct TYPE_36__ {int nWidth; TYPE_5__ pt; TYPE_8__* next_marked; TYPE_8__* next_para; TYPE_8__* prev_para; int /*<<< orphan*/  nCharOfs; } ;
struct TYPE_32__ {TYPE_7__ para; } ;
struct TYPE_37__ {scalar_t__ type; TYPE_3__ member; } ;
struct TYPE_30__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_35__ {int nTotalWidth; scalar_t__ nTotalLength; scalar_t__ nLastTotalLength; TYPE_4__* pBuffer; TYPE_1__ sizeWindow; TYPE_8__* first_marked_para; int /*<<< orphan*/  texthost; } ;
struct TYPE_33__ {TYPE_8__* pLast; } ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  TYPE_7__ ME_Paragraph ;
typedef  TYPE_8__ ME_DisplayItem ;
typedef  TYPE_9__ ME_Context ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  ITextHost_TxGetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_DestroyContext (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_InitContext (TYPE_9__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_InvalidateParagraphRange (TYPE_6__*,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ME_MarkRepaintEnd (TYPE_8__*,TYPE_8__**,TYPE_8__**) ; 
 int /*<<< orphan*/  ME_WrapTextParagraph (TYPE_6__*,TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  adjust_para_y (TYPE_8__*,TYPE_9__*,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diParagraph ; 
 int get_total_width (TYPE_6__*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  remove_marked_para (TYPE_6__*,TYPE_8__*) ; 

BOOL ME_WrapMarkedParagraphs(ME_TextEditor *editor)
{
  ME_DisplayItem *item;
  ME_Context c;
  int totalWidth = editor->nTotalWidth, diff = 0, prev_width;
  ME_DisplayItem *repaint_start = NULL, *repaint_end = NULL;
  ME_Paragraph *para;

  if (!editor->first_marked_para)
    return FALSE;

  ME_InitContext(&c, editor, ITextHost_TxGetDC(editor->texthost));

  item = editor->first_marked_para;
  c.pt = item->member.para.pt;
  while (item != editor->pBuffer->pLast)
  {
    assert(item->type == diParagraph);

    prev_width = item->member.para.nWidth;
    ME_WrapTextParagraph(editor, &c, item);
    if (prev_width == totalWidth && item->member.para.nWidth < totalWidth)
      totalWidth = get_total_width(editor);
    else
      totalWidth = max(totalWidth, item->member.para.nWidth);

    if (!item->member.para.nCharOfs)
      ME_MarkRepaintEnd(item->member.para.prev_para, &repaint_start, &repaint_end);
    ME_MarkRepaintEnd(item, &repaint_start, &repaint_end);
    adjust_para_y(item, &c, repaint_start, repaint_end);

    if (item->member.para.next_para)
    {
      diff = c.pt.y - item->member.para.next_para->member.para.pt.y;
      if (diff)
      {
        para = &item->member.para;
        while (para->next_para && para != &item->member.para.next_marked->member.para &&
               para != &editor->pBuffer->pLast->member.para)
        {
          ME_MarkRepaintEnd(para->next_para, &repaint_start, &repaint_end);
          para->next_para->member.para.pt.y = c.pt.y;
          adjust_para_y(para->next_para, &c, repaint_start, repaint_end);
          para = &para->next_para->member.para;
        }
      }
    }
    if (item->member.para.next_marked)
    {
      ME_DisplayItem *rem = item;
      item = item->member.para.next_marked;
      remove_marked_para(editor, rem);
    }
    else
    {
      remove_marked_para(editor, item);
      item = editor->pBuffer->pLast;
    }
    c.pt.y = item->member.para.pt.y;
  }
  editor->sizeWindow.cx = c.rcView.right-c.rcView.left;
  editor->sizeWindow.cy = c.rcView.bottom-c.rcView.top;

  editor->nTotalLength = c.pt.y;
  editor->nTotalWidth = totalWidth;
  editor->pBuffer->pLast->member.para.pt.x = 0;
  editor->pBuffer->pLast->member.para.pt.y = c.pt.y;

  ME_DestroyContext(&c);

  if (repaint_start || editor->nTotalLength < editor->nLastTotalLength)
    ME_InvalidateParagraphRange(editor, repaint_start, repaint_end);
  return !!repaint_start;
}