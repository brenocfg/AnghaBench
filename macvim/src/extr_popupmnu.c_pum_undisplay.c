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
 int /*<<< orphan*/  SOME_VALID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * pum_array ; 
 int /*<<< orphan*/  redraw_all_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redraw_tabline ; 
 int /*<<< orphan*/  status_redraw_all () ; 

void
pum_undisplay()
{
    pum_array = NULL;
    redraw_all_later(SOME_VALID);
#ifdef FEAT_WINDOWS
    redraw_tabline = TRUE;
#endif
    status_redraw_all();
}