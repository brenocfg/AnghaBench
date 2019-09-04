#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * id; int /*<<< orphan*/ * submenu_id; int /*<<< orphan*/  name; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ vimmenu_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_MENU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * gtk_menu_item_new () ; 
 int /*<<< orphan*/  gtk_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_is_popup (int /*<<< orphan*/ ) ; 
 scalar_t__ menu_is_separator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_item_activate ; 
 int /*<<< orphan*/  menu_item_new (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
gui_mch_add_menu_item(vimmenu_T *menu, int idx)
{
    vimmenu_T *parent;

    parent = menu->parent;

# ifdef FEAT_TOOLBAR
    if (menu_is_toolbar(parent->name))
    {
	GtkToolbar *toolbar;

	toolbar = GTK_TOOLBAR(gui.toolbar);
	menu->submenu_id = NULL;

	if (menu_is_separator(menu->name))
	{
	    gtk_toolbar_insert_space(toolbar, idx);
	    menu->id = NULL;
	}
	else
	{
	    char_u *text;
	    char_u *tooltip;

	    text    = CONVERT_TO_UTF8(menu->dname);
	    tooltip = CONVERT_TO_UTF8(menu->strings[MENU_INDEX_TIP]);
	    if (tooltip != NULL && !utf_valid_string(tooltip, NULL))
		/* Invalid text, can happen when 'encoding' is changed.  Avoid
		 * a nasty GTK error message, skip the tooltip. */
		CONVERT_TO_UTF8_FREE(tooltip);

	    menu->id = gtk_toolbar_insert_item(
		    toolbar,
		    (const char *)text,
		    (const char *)tooltip,
		    NULL,
		    create_menu_icon(menu, gtk_toolbar_get_icon_size(toolbar)),
		    G_CALLBACK(&menu_item_activate),
		    menu,
		    idx);

	    if (gtk_socket_id != 0)
		gtk_signal_connect(GTK_OBJECT(menu->id), "focus_in_event",
			GTK_SIGNAL_FUNC(toolbar_button_focus_in_event), NULL);

	    CONVERT_TO_UTF8_FREE(text);
	    CONVERT_TO_UTF8_FREE(tooltip);
	}
    }
    else
# endif /* FEAT_TOOLBAR */
    {
	/* No parent, must be a non-menubar menu */
	if (parent == NULL || parent->submenu_id == NULL)
	    return;

	/* Make place for the possible tearoff handle item.  Not in the popup
	 * menu, it doesn't have a tearoff item. */
	if (!menu_is_popup(parent->name))
	    ++idx;

	if (menu_is_separator(menu->name))
	{
	    /* Separator: Just add it */
	    menu->id = gtk_menu_item_new();
	    gtk_widget_set_sensitive(menu->id, FALSE);
	    gtk_widget_show(menu->id);
	    gtk_menu_insert(GTK_MENU(parent->submenu_id), menu->id, idx);

	    return;
	}

	/* Add textual menu item. */
	menu_item_new(menu, parent->submenu_id);
	gtk_widget_show(menu->id);
	gtk_menu_insert(GTK_MENU(parent->submenu_id), menu->id, idx);

	if (menu->id != NULL)
	    gtk_signal_connect(GTK_OBJECT(menu->id), "activate",
			       GTK_SIGNAL_FUNC(menu_item_activate), menu);
    }
}