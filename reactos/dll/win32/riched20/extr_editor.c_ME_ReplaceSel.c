#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_ClearTempStyle (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_EmptyUndoStack (TYPE_1__*) ; 
 int /*<<< orphan*/ * ME_GetSelectionInsertStyle (TYPE_1__*) ; 
 int ME_GetSelectionOfs (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  ME_InsertTextFromCursor (TYPE_1__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_InternalDeleteText (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_UpdateSelectionLinkAttribute (TYPE_1__*) ; 

void ME_ReplaceSel(ME_TextEditor *editor, BOOL can_undo, const WCHAR *str, int len)
{
  int from, to, nStartCursor;
  ME_Style *style;

  nStartCursor = ME_GetSelectionOfs(editor, &from, &to);
  style = ME_GetSelectionInsertStyle(editor);
  ME_InternalDeleteText(editor, &editor->pCursors[nStartCursor], to-from, FALSE);
  ME_InsertTextFromCursor(editor, 0, str, len, style);
  ME_ReleaseStyle(style);
  /* drop temporary style if line end */
  /*
   * FIXME question: does abc\n mean: put abc,
   * clear temp style, put \n? (would require a change)
   */
  if (len>0 && str[len-1] == '\n')
    ME_ClearTempStyle(editor);
  ME_CommitUndo(editor);
  ME_UpdateSelectionLinkAttribute(editor);
  if (!can_undo)
    ME_EmptyUndoStack(editor);
  ME_UpdateRepaint(editor, FALSE);
}