#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct srcpos {int first_column; int last_column; scalar_t__ last_line; scalar_t__ first_line; TYPE_1__* file; } ;
struct TYPE_2__ {int colno; scalar_t__ lineno; } ;

/* Variables and functions */
 TYPE_1__* current_srcfile ; 

void srcpos_update(struct srcpos *pos, const char *text, int len)
{
	int i;

	pos->file = current_srcfile;

	pos->first_line = current_srcfile->lineno;
	pos->first_column = current_srcfile->colno;

	for (i = 0; i < len; i++)
		if (text[i] == '\n') {
			current_srcfile->lineno++;
			current_srcfile->colno = 1;
		} else {
			current_srcfile->colno++;
		}

	pos->last_line = current_srcfile->lineno;
	pos->last_column = current_srcfile->colno;
}