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
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_init_which_components (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gui_update_scrollbars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  need_mouse_correct ; 
 int /*<<< orphan*/  out_flush () ; 
 scalar_t__ starting ; 

void
gui_may_update_scrollbars()
{
    if (gui.in_use && starting == 0)
    {
	out_flush();
	gui_init_which_components(NULL);
	gui_update_scrollbars(TRUE);
    }
    need_mouse_correct = TRUE;
}