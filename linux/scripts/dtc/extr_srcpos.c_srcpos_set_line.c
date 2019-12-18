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
struct TYPE_2__ {char* name; int lineno; } ;

/* Variables and functions */
 TYPE_1__* current_srcfile ; 
 int initial_cpp ; 
 int /*<<< orphan*/  set_initial_path (char*) ; 

void srcpos_set_line(char *f, int l)
{
	current_srcfile->name = f;
	current_srcfile->lineno = l;

	if (initial_cpp) {
		initial_cpp = false;
		set_initial_path(f);
	}
}