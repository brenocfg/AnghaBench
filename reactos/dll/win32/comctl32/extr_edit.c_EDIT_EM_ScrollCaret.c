#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ right; scalar_t__ left; } ;
struct TYPE_12__ {int style; scalar_t__ char_width; scalar_t__ selection_end; int flags; scalar_t__ y_offset; scalar_t__ line_count; scalar_t__ x_offset; scalar_t__ text_width; TYPE_1__ format_rect; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ EDIT_EM_LineFromChar (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_EM_LineScroll_internal (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_EM_PosFromChar (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  EDIT_SetCaretPos (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EF_AFTER_WRAP ; 
 int EF_FOCUSED ; 
 int ES_MULTILINE ; 
 int FALSE ; 
 scalar_t__ HSCROLL_FRACTION ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_text_length (TYPE_2__*) ; 
 scalar_t__ get_vertical_line_count (TYPE_2__*) ; 

__attribute__((used)) static void EDIT_EM_ScrollCaret(EDITSTATE *es)
{
	if (es->style & ES_MULTILINE) {
		INT l;
		INT vlc;
		INT ww;
		INT cw = es->char_width;
		INT x;
		INT dy = 0;
		INT dx = 0;

		l = EDIT_EM_LineFromChar(es, es->selection_end);
		x = (short)LOWORD(EDIT_EM_PosFromChar(es, es->selection_end, es->flags & EF_AFTER_WRAP));
		vlc = get_vertical_line_count(es);
		if (l >= es->y_offset + vlc)
			dy = l - vlc + 1 - es->y_offset;
		if (l < es->y_offset)
			dy = l - es->y_offset;
		ww = es->format_rect.right - es->format_rect.left;
		if (x < es->format_rect.left)
			dx = x - es->format_rect.left - ww / HSCROLL_FRACTION / cw * cw;
		if (x > es->format_rect.right)
			dx = x - es->format_rect.left - (HSCROLL_FRACTION - 1) * ww / HSCROLL_FRACTION / cw * cw;
		if (dy || dx || (es->y_offset && (es->line_count - es->y_offset < vlc)))
		{
		    /* check if we are going to move too far */
		    if(es->x_offset + dx + ww > es->text_width)
			dx = es->text_width - ww - es->x_offset;
		    if(dx || dy || (es->y_offset && (es->line_count - es->y_offset < vlc)))
			EDIT_EM_LineScroll_internal(es, dx, dy);
		}
	} else {
		INT x;
		INT goal;
		INT format_width;

		x = (short)LOWORD(EDIT_EM_PosFromChar(es, es->selection_end, FALSE));
		format_width = es->format_rect.right - es->format_rect.left;
		if (x < es->format_rect.left) {
			goal = es->format_rect.left + format_width / HSCROLL_FRACTION;
			do {
				es->x_offset--;
				x = (short)LOWORD(EDIT_EM_PosFromChar(es, es->selection_end, FALSE));
			} while ((x < goal) && es->x_offset);
			/* FIXME: use ScrollWindow() somehow to improve performance */
			EDIT_UpdateText(es, NULL, TRUE);
		} else if (x > es->format_rect.right) {
			INT x_last;
			INT len = get_text_length(es);
			goal = es->format_rect.right - format_width / HSCROLL_FRACTION;
			do {
				es->x_offset++;
				x = (short)LOWORD(EDIT_EM_PosFromChar(es, es->selection_end, FALSE));
				x_last = (short)LOWORD(EDIT_EM_PosFromChar(es, len, FALSE));
			} while ((x > goal) && (x_last > es->format_rect.right));
			/* FIXME: use ScrollWindow() somehow to improve performance */
			EDIT_UpdateText(es, NULL, TRUE);
		}
	}

    if(es->flags & EF_FOCUSED)
	EDIT_SetCaretPos(es, es->selection_end, es->flags & EF_AFTER_WRAP);
}