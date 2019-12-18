#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int selection_end; int style; char* text; int selection_start; } ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static void EDIT_MoveBackward(EDITSTATE *es, BOOL extend)
{
	INT e = es->selection_end;

	if (e) {
		e--;
		if ((es->style & ES_MULTILINE) && e &&
				(es->text[e - 1] == '\r') && (es->text[e] == '\n')) {
			e--;
			if (e && (es->text[e - 1] == '\r'))
				e--;
		}
	}
	EDIT_EM_SetSel(es, extend ? es->selection_start : e, e, FALSE);
	EDIT_EM_ScrollCaret(es);
}