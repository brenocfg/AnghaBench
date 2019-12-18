#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int style; int flags; scalar_t__ selection_start; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  x_offset; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ EDIT_CharFromPos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_EM_PosFromChar (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int EF_AFTER_WRAP ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_MoveHome(EDITSTATE *es, BOOL extend, BOOL ctrl)
{
	INT e;

	/* Pass the x_offset in x to make sure of receiving the first position of the line */
	if (!ctrl && (es->style & ES_MULTILINE))
		e = EDIT_CharFromPos(es, -es->x_offset,
			HIWORD(EDIT_EM_PosFromChar(es, es->selection_end, es->flags & EF_AFTER_WRAP)), NULL);
	else
		e = 0;
	EDIT_EM_SetSel(es, extend ? es->selection_start : e, e, FALSE);
	EDIT_EM_ScrollCaret(es);
}