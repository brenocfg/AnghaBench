#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * submenu_id; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {int /*<<< orphan*/  event_time; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkMenuPositionFunc ;

/* Variables and functions */
 int /*<<< orphan*/ * CONVERT_TO_UTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONVERT_TO_UTF8_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_IM_MULTICONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_SHELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _ (char*) ; 
 int /*<<< orphan*/ * g_object_get_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_object_set_data (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_im_multicontext_append_menuitems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_menu_item_new_with_mnemonic (char const*) ; 
 int /*<<< orphan*/  gtk_menu_item_set_submenu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_menu_new () ; 
 int /*<<< orphan*/  gtk_menu_popup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_shell_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_separator_menu_item_new () ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/ * xic ; 

void
gui_mch_show_popupmenu(vimmenu_T *menu)
{
# if defined(FEAT_XIM)
    /*
     * Append a submenu for selecting an input method.	This is
     * currently the only way to switch input methods at runtime.
     */
    if (xic != NULL && g_object_get_data(G_OBJECT(menu->submenu_id),
					 "vim-has-im-menu") == NULL)
    {
	GtkWidget   *menuitem;
	GtkWidget   *submenu;
	char_u	    *name;

	menuitem = gtk_separator_menu_item_new();
	gtk_widget_show(menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->submenu_id), menuitem);

	name = (char_u *)_("Input _Methods");
	name = CONVERT_TO_UTF8(name);
	menuitem = gtk_menu_item_new_with_mnemonic((const char *)name);
	CONVERT_TO_UTF8_FREE(name);
	gtk_widget_show(menuitem);

	submenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), submenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->submenu_id), menuitem);

	gtk_im_multicontext_append_menuitems(GTK_IM_MULTICONTEXT(xic),
					     GTK_MENU_SHELL(submenu));
	g_object_set_data(G_OBJECT(menu->submenu_id),
			  "vim-has-im-menu", GINT_TO_POINTER(TRUE));
    }
# endif /* FEAT_XIM */

    gtk_menu_popup(GTK_MENU(menu->submenu_id),
		   NULL, NULL,
		   (GtkMenuPositionFunc)NULL, NULL,
		   3U, gui.event_time);
}