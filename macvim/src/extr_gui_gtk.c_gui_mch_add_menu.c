#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int /*<<< orphan*/  tearoff_handle; int /*<<< orphan*/ * submenu_id; int /*<<< orphan*/  id; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ vimmenu_T ;
struct TYPE_6__ {int /*<<< orphan*/  accel_group; int /*<<< orphan*/ * menubar; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GO_TEAROFF ; 
 int /*<<< orphan*/  GTK_MENU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_MENU_SHELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_menu_item_set_submenu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* gtk_menu_new () ; 
 int /*<<< orphan*/  gtk_menu_prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_set_accel_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_shell_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tearoff_menu_item_new () ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  menu_is_menubar (char*) ; 
 scalar_t__ menu_is_popup (char*) ; 
 int /*<<< orphan*/  menu_item_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_add_menu(vimmenu_T *menu, int idx)
{
    vimmenu_T	*parent;
    GtkWidget	*parent_widget;

    if (menu->name[0] == ']' || menu_is_popup(menu->name))
    {
	menu->submenu_id = gtk_menu_new();
	return;
    }

    parent = menu->parent;

    if ((parent != NULL && parent->submenu_id == NULL)
	    || !menu_is_menubar(menu->name))
	return;

    parent_widget = (parent != NULL) ? parent->submenu_id : gui.menubar;
    menu_item_new(menu, parent_widget);

    /* since the tearoff should always appear first, increment idx */
    if (parent != NULL && !menu_is_popup(parent->name))
	++idx;

    gtk_menu_shell_insert(GTK_MENU_SHELL(parent_widget), menu->id, idx);

    menu->submenu_id = gtk_menu_new();

    gtk_menu_set_accel_group(GTK_MENU(menu->submenu_id), gui.accel_group);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->id), menu->submenu_id);

    menu->tearoff_handle = gtk_tearoff_menu_item_new();
    if (vim_strchr(p_go, GO_TEAROFF) != NULL)
	gtk_widget_show(menu->tearoff_handle);
    gtk_menu_prepend(GTK_MENU(menu->submenu_id), menu->tearoff_handle);
}