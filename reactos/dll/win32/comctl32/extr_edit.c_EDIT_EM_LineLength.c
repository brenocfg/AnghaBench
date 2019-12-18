#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int style; int selection_start; int selection_end; TYPE_1__* first_line_def; } ;
struct TYPE_7__ {int net_length; scalar_t__ length; struct TYPE_7__* next; } ;
typedef  TYPE_1__ LINEDEF ;
typedef  int INT32 ;
typedef  int INT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 int EDIT_EM_LineFromChar (TYPE_2__*,int) ; 
 int EDIT_EM_LineIndex (TYPE_2__*,int) ; 
 int ES_MULTILINE ; 
 int get_text_length (TYPE_2__*) ; 

__attribute__((used)) static INT EDIT_EM_LineLength(EDITSTATE *es, INT index)
{
	LINEDEF *line_def;

	if (!(es->style & ES_MULTILINE))
		return get_text_length(es);

	if (index == -1) {
		/* get the number of remaining non-selected chars of selected lines */
		INT32 l; /* line number */
		INT32 li; /* index of first char in line */
		INT32 count;
		l = EDIT_EM_LineFromChar(es, es->selection_start);
		/* # chars before start of selection area */
		count = es->selection_start - EDIT_EM_LineIndex(es, l);
		l = EDIT_EM_LineFromChar(es, es->selection_end);
		/* # chars after end of selection */
		li = EDIT_EM_LineIndex(es, l);
		count += li + EDIT_EM_LineLength(es, li) - es->selection_end;
		return count;
	}
	line_def = es->first_line_def;
	index -= line_def->length;
	while ((index >= 0) && line_def->next) {
		line_def = line_def->next;
		index -= line_def->length;
	}
	return line_def->net_length;
}