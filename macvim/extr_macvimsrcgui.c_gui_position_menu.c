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
struct TYPE_2__ {int /*<<< orphan*/  menu_height; int /*<<< orphan*/  menu_width; scalar_t__ in_use; scalar_t__ menu_is_active; } ;

/* Variables and functions */
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_mch_set_menu_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_position_menu()
{
# if !(defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MOTIF) \
        || defined(FEAT_GUI_MACVIM))
    if (gui.menu_is_active && gui.in_use)
	gui_mch_set_menu_pos(0, 0, gui.menu_width, gui.menu_height);
# endif
}