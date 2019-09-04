#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int Columns ; 
 int Rows ; 
 int /*<<< orphan*/  check_shellsize () ; 
 int /*<<< orphan*/  exiting ; 
 int /*<<< orphan*/  shell_resized () ; 
 int /*<<< orphan*/  ui_get_shellsize () ; 

void
shell_resized_check()
{
    int		old_Rows = Rows;
    int		old_Columns = Columns;

    if (!exiting
#ifdef FEAT_GUI
	    /* Do not get the size when executing a shell command during
	     * startup. */
	    && !gui.starting
#endif
	    )
    {
	(void)ui_get_shellsize();
	check_shellsize();
	if (old_Rows != Rows || old_Columns != Columns)
	    shell_resized();
    }
}