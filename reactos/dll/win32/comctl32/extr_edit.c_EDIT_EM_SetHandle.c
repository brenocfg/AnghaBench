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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int style; int buffer_size; int /*<<< orphan*/  flags; scalar_t__ selection_end; scalar_t__ selection_start; scalar_t__ y_offset; scalar_t__ x_offset; int /*<<< orphan*/ * hlocapp; scalar_t__ hloc32W; } ;
typedef  scalar_t__ HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_BuildLineDefs_ML (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_EM_EmptyUndoBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_LockBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_UnlockBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_MODIFIED ; 
 int /*<<< orphan*/  EF_UPDATE ; 
 int ES_MULTILINE ; 
 int LocalSize (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_text_length (TYPE_1__*) ; 
 int /*<<< orphan*/  text_buffer_changed (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_EM_SetHandle(EDITSTATE *es, HLOCAL hloc)
{
    if (!(es->style & ES_MULTILINE))
        return;

    if (!hloc)
        return;

    EDIT_UnlockBuffer(es, TRUE);

    es->hloc32W = hloc;
    es->buffer_size = LocalSize(es->hloc32W)/sizeof(WCHAR) - 1;

    /* The text buffer handle belongs to the control */
    es->hlocapp = NULL;

    EDIT_LockBuffer(es);
    text_buffer_changed(es);

    es->x_offset = es->y_offset = 0;
    es->selection_start = es->selection_end = 0;
    EDIT_EM_EmptyUndoBuffer(es);
    es->flags &= ~EF_MODIFIED;
    es->flags &= ~EF_UPDATE;
    EDIT_BuildLineDefs_ML(es, 0, get_text_length(es), 0, NULL);
    EDIT_UpdateText(es, NULL, TRUE);
    EDIT_EM_ScrollCaret(es);
    /* force scroll info update */
    EDIT_UpdateScrollInfo(es);
}