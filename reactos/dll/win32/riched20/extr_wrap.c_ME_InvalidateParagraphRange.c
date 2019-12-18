#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_25__ {TYPE_5__ rcView; } ;
struct TYPE_19__ {scalar_t__ y; } ;
struct TYPE_20__ {scalar_t__ nHeight; TYPE_2__ pt; } ;
struct TYPE_21__ {TYPE_3__ para; } ;
struct TYPE_24__ {TYPE_4__ member; } ;
struct TYPE_18__ {int nPos; } ;
struct TYPE_23__ {scalar_t__ nTotalLength; scalar_t__ nLastTotalLength; int /*<<< orphan*/  texthost; TYPE_1__ vert_si; } ;
typedef  TYPE_5__ RECT ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  TYPE_7__ ME_DisplayItem ;
typedef  TYPE_8__ ME_Context ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_TxGetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxInvalidateRect (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_DestroyContext (TYPE_8__*) ; 
 TYPE_7__* ME_GetOuterParagraph (TYPE_7__*) ; 
 int /*<<< orphan*/  ME_InitContext (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

void ME_InvalidateParagraphRange(ME_TextEditor *editor,
                                 ME_DisplayItem *start_para,
                                 ME_DisplayItem *last_para)
{
  ME_Context c;
  RECT rc;
  int ofs;

  ME_InitContext(&c, editor, ITextHost_TxGetDC(editor->texthost));
  rc = c.rcView;
  ofs = editor->vert_si.nPos;

  if (start_para) {
    start_para = ME_GetOuterParagraph(start_para);
    last_para = ME_GetOuterParagraph(last_para);
    rc.top = c.rcView.top + start_para->member.para.pt.y - ofs;
  } else {
    rc.top = c.rcView.top + editor->nTotalLength - ofs;
  }
  if (editor->nTotalLength < editor->nLastTotalLength)
    rc.bottom = c.rcView.top + editor->nLastTotalLength - ofs;
  else
    rc.bottom = c.rcView.top + last_para->member.para.pt.y + last_para->member.para.nHeight - ofs;
  ITextHost_TxInvalidateRect(editor->texthost, &rc, TRUE);

  ME_DestroyContext(&c);
}