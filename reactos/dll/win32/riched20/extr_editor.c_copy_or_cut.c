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
struct TYPE_8__ {int styleFlags; int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ES_READONLY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_1__*) ; 
 scalar_t__ ME_Copy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int ME_GetSelectionOfs (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  ME_InternalDeleteText (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL copy_or_cut(ME_TextEditor *editor, BOOL cut)
{
    BOOL result;
    int offs, num_chars;
    int start_cursor = ME_GetSelectionOfs(editor, &offs, &num_chars);
    ME_Cursor *sel_start = &editor->pCursors[start_cursor];

    if (cut && (editor->styleFlags & ES_READONLY))
    {
        MessageBeep(MB_ICONERROR);
        return FALSE;
    }

    num_chars -= offs;
    result = ME_Copy(editor, sel_start, num_chars);
    if (result && cut)
    {
        ME_InternalDeleteText(editor, sel_start, num_chars, FALSE);
        ME_CommitUndo(editor);
        ME_UpdateRepaint(editor, TRUE);
    }
    return result;
}