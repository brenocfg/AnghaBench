#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * id; int /*<<< orphan*/ * submenu_id; } ;
typedef  TYPE_1__ vimmenu_T ;

/* Variables and functions */
 int /*<<< orphan*/  PtDestroyWidget (int /*<<< orphan*/ *) ; 

void
gui_mch_destroy_menu(vimmenu_T *menu)
{
    if (menu->submenu_id != NULL)
	PtDestroyWidget(menu->submenu_id);
    if (menu->id != NULL)
	PtDestroyWidget(menu->id);

    menu->submenu_id = NULL;
    menu->id = NULL;
}