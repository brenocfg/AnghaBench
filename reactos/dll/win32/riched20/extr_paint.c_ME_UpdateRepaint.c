#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nEventMask; int /*<<< orphan*/  texthost; int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ENM_CHANGE ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  ITextHost_TxViewChange (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ME_EnsureVisible (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SendOldNotify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SendSelChange (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_UpdateScrollBar (TYPE_1__*) ; 
 scalar_t__ ME_WrapMarkedParagraphs (TYPE_1__*) ; 

void ME_UpdateRepaint(ME_TextEditor *editor, BOOL update_now)
{
  /* Should be called whenever the contents of the control have changed */
  BOOL wrappedParagraphs;

  wrappedParagraphs = ME_WrapMarkedParagraphs(editor);
  if (wrappedParagraphs)
    ME_UpdateScrollBar(editor);

  /* Ensure that the cursor is visible */
  ME_EnsureVisible(editor, &editor->pCursors[0]);

  ITextHost_TxViewChange(editor->texthost, update_now);

  ME_SendSelChange(editor);

  /* send EN_CHANGE if the event mask asks for it */
  if(editor->nEventMask & ENM_CHANGE)
  {
    editor->nEventMask &= ~ENM_CHANGE;
    ME_SendOldNotify(editor, EN_CHANGE);
    editor->nEventMask |= ENM_CHANGE;
  }
}