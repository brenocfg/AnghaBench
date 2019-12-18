#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nPos; } ;
struct TYPE_11__ {scalar_t__ nPos; } ;
struct TYPE_13__ {scalar_t__ nSelectionType; int /*<<< orphan*/  texthost; int /*<<< orphan*/ * pCursors; int /*<<< orphan*/  bCaretAtEnd; TYPE_2__ vert_si; TYPE_1__ horz_si; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_EnsureVisible (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ExtendAnchorSelection (TYPE_3__*) ; 
 int /*<<< orphan*/  ME_FindPixelPos (TYPE_3__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_InvalidateSelection (TYPE_3__*) ; 
 int /*<<< orphan*/  ME_SendSelChange (TYPE_3__*) ; 
 int /*<<< orphan*/  ME_ShowCaret (TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stDocument ; 
 scalar_t__ stPosition ; 

void ME_MouseMove(ME_TextEditor *editor, int x, int y)
{
  ME_Cursor tmp_cursor;

  if (editor->nSelectionType == stDocument)
      return;
  x += editor->horz_si.nPos;
  y += editor->vert_si.nPos;

  tmp_cursor = editor->pCursors[0];
  /* FIXME: do something with the return value of ME_FindPixelPos */
  ME_FindPixelPos(editor, x, y, &tmp_cursor, &editor->bCaretAtEnd, TRUE);

  ME_InvalidateSelection(editor);
  editor->pCursors[0] = tmp_cursor;
  ME_ExtendAnchorSelection(editor);

  if (editor->nSelectionType != stPosition &&
      memcmp(&editor->pCursors[1], &editor->pCursors[3], sizeof(ME_Cursor)))
  {
      /* The scroll the cursor towards the other end, since it was the one
       * extended by ME_ExtendAnchorSelection */
      ME_EnsureVisible(editor, &editor->pCursors[1]);
  } else {
      ME_EnsureVisible(editor, &editor->pCursors[0]);
  }

  ME_InvalidateSelection(editor);
  ITextHost_TxShowCaret(editor->texthost, FALSE);
  ME_ShowCaret(editor);
  ME_SendSelChange(editor);
}