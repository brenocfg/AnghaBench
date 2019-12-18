#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {short left; short right; scalar_t__ top; } ;
struct TYPE_11__ {int style; int y_offset; int line_height; int line_count; int selection_end; TYPE_1__ format_rect; scalar_t__ ssa; TYPE_3__* first_line_def; } ;
struct TYPE_10__ {int length; scalar_t__ ssa; struct TYPE_10__* next; } ;
struct TYPE_9__ {int right; int left; scalar_t__ top; scalar_t__ bottom; } ;
typedef  scalar_t__ SCRIPT_STRING_ANALYSIS ;
typedef  TYPE_2__* LPRECT ;
typedef  TYPE_3__ LINEDEF ;
typedef  int INT ;
typedef  TYPE_4__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_PosFromChar (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptStringCPtoX (scalar_t__,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void EDIT_GetLineRect(EDITSTATE *es, INT line, INT scol, INT ecol, LPRECT rc)
{
	SCRIPT_STRING_ANALYSIS ssa;
	INT line_index = 0;
	INT pt1, pt2, pt3;

	if (es->style & ES_MULTILINE)
	{
		const LINEDEF *line_def = NULL;
		rc->top = es->format_rect.top + (line - es->y_offset) * es->line_height;
		if (line >= es->line_count)
			return;

		line_def = es->first_line_def;
		if (line == -1) {
			INT index = es->selection_end - line_def->length;
			while ((index >= 0) && line_def->next) {
				line_index += line_def->length;
				line_def = line_def->next;
				index -= line_def->length;
			}
		} else {
			while (line > 0) {
				line_index += line_def->length;
				line_def = line_def->next;
				line--;
			}
		}
		ssa = line_def->ssa;
	}
	else
	{
		line_index = 0;
		rc->top = es->format_rect.top;
		ssa = es->ssa;
	}

	rc->bottom = rc->top + es->line_height;
	pt1 = (scol == 0) ? es->format_rect.left : (short)LOWORD(EDIT_EM_PosFromChar(es, line_index + scol, TRUE));
	pt2 = (ecol == -1) ? es->format_rect.right : (short)LOWORD(EDIT_EM_PosFromChar(es, line_index + ecol, TRUE));
	if (ssa)
	{
		ScriptStringCPtoX(ssa, scol, FALSE, &pt3);
		pt3+=es->format_rect.left;
	}
	else pt3 = pt1;
	rc->right = max(max(pt1 , pt2),pt3);
	rc->left = min(min(pt1, pt2),pt3);
}