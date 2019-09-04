#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ vimmenu_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_WIDGET_SENSITIVE (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gui_mch_menu_hidden (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mch_update () ; 
 scalar_t__ menu_is_separator (int /*<<< orphan*/ ) ; 

void
gui_mch_menu_grey(vimmenu_T *menu, int grey)
{
    if (menu->id == NULL)
	return;

    if (menu_is_separator(menu->name))
	grey = TRUE;

    gui_mch_menu_hidden(menu, FALSE);
    /* Be clever about bitfields versus true booleans here! */
    if (!GTK_WIDGET_SENSITIVE(menu->id) == !grey)
    {
	gtk_widget_set_sensitive(menu->id, !grey);
	gui_mch_update();
    }
}