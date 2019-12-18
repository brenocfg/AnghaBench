#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ selection_start; scalar_t__ selection_end; int style; int line_count; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ EDIT_CallWordBreakProc (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ EDIT_EM_LineFromChar (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineIndex (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineLength (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WB_RIGHT ; 

__attribute__((used)) static void EDIT_MoveWordForward(EDITSTATE *es, BOOL extend)
{
	INT s = es->selection_start;
	INT e = es->selection_end;
	INT l;
	INT ll;
	INT li;

	l = EDIT_EM_LineFromChar(es, e);
	ll = EDIT_EM_LineLength(es, e);
	li = EDIT_EM_LineIndex(es, l);
	if (e - li == ll) {
		if ((es->style & ES_MULTILINE) && (l != es->line_count - 1))
			e = EDIT_EM_LineIndex(es, l + 1);
	} else {
		e = li + EDIT_CallWordBreakProc(es,
				li, e - li + 1, ll, WB_RIGHT);
	}
	if (!extend)
		s = e;
	EDIT_EM_SetSel(es, s, e, FALSE);
	EDIT_EM_ScrollCaret(es);
}