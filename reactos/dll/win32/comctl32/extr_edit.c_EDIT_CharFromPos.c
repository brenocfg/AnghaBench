#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; scalar_t__ left; int right; } ;
struct TYPE_12__ {int style; scalar_t__ line_height; scalar_t__ y_offset; scalar_t__ x_offset; scalar_t__ text_width; scalar_t__ ssa; TYPE_1__ format_rect; TYPE_3__* first_line_def; } ;
struct TYPE_11__ {scalar_t__ length; int width; scalar_t__ ending; scalar_t__ net_length; scalar_t__ ssa; struct TYPE_11__* next; } ;
struct TYPE_10__ {scalar_t__ cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  int* LPBOOL ;
typedef  TYPE_3__ LINEDEF ;
typedef  scalar_t__ INT ;
typedef  TYPE_4__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_UpdateUniscribeData (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ END_WRAP ; 
 int ES_CENTER ; 
 int ES_MULTILINE ; 
 int ES_RIGHT ; 
 int FALSE ; 
 int /*<<< orphan*/  ScriptStringCPtoX (scalar_t__,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  ScriptStringXtoCP (scalar_t__,scalar_t__,scalar_t__*,...) ; 
 TYPE_2__* ScriptString_pSize (scalar_t__) ; 
 scalar_t__ get_text_length (TYPE_4__*) ; 

__attribute__((used)) static INT EDIT_CharFromPos(EDITSTATE *es, INT x, INT y, LPBOOL after_wrap)
{
	INT index;

	if (es->style & ES_MULTILINE) {
		int trailing;
		INT line = (y - es->format_rect.top) / es->line_height + es->y_offset;
		INT line_index = 0;
		LINEDEF *line_def = es->first_line_def;
		EDIT_UpdateUniscribeData(es, NULL, line);
		while ((line > 0) && line_def->next) {
			line_index += line_def->length;
			line_def = line_def->next;
			line--;
		}

		x += es->x_offset - es->format_rect.left;
		if (es->style & ES_RIGHT)
			x -= (es->format_rect.right - es->format_rect.left) - line_def->width;
		else if (es->style & ES_CENTER)
			x -= ((es->format_rect.right - es->format_rect.left) - line_def->width) / 2;
		if (x >= line_def->width) {
			if (after_wrap)
				*after_wrap = (line_def->ending == END_WRAP);
			return line_index + line_def->net_length;
		}
		if (x <= 0 || !line_def->ssa) {
			if (after_wrap)
				*after_wrap = FALSE;
			return line_index;
		}

		ScriptStringXtoCP(line_def->ssa, x , &index, &trailing);
		if (trailing) index++;
		index += line_index;
		if (after_wrap)
			*after_wrap = ((index == line_index + line_def->net_length) &&
							(line_def->ending == END_WRAP));
	} else {
		INT xoff = 0;
		INT trailing;
		if (after_wrap)
			*after_wrap = FALSE;
		x -= es->format_rect.left;
		if (!x)
			return es->x_offset;

		if (!es->x_offset)
		{
			INT indent = (es->format_rect.right - es->format_rect.left) - es->text_width;
			if (es->style & ES_RIGHT)
				x -= indent;
			else if (es->style & ES_CENTER)
				x -= indent / 2;
		}

		EDIT_UpdateUniscribeData(es, NULL, 0);
		if (es->x_offset)
		{
			if (es->ssa)
			{
				if (es->x_offset>= get_text_length(es))
				{
					const SIZE *size;
					size = ScriptString_pSize(es->ssa);
					xoff = size->cx;
				}
				ScriptStringCPtoX(es->ssa, es->x_offset, FALSE, &xoff);
			}
			else
				xoff = 0;
		}
		if (x < 0)
		{
			if (x + xoff > 0 || !es->ssa)
			{
				ScriptStringXtoCP(es->ssa, x+xoff, &index, &trailing);
				if (trailing) index++;
			}
			else
				index = 0;
		}
		else
		{
			if (x)
			{
				const SIZE *size = NULL;
				if (es->ssa)
					size = ScriptString_pSize(es->ssa);
				if (!size)
					index = 0;
				else if (x > size->cx)
					index = get_text_length(es);
				else if (es->ssa)
				{
					ScriptStringXtoCP(es->ssa, x+xoff, &index, &trailing);
					if (trailing) index++;
				}
				else
					index = 0;
			}
			else
				index = es->x_offset;
		}
	}
	return index;
}