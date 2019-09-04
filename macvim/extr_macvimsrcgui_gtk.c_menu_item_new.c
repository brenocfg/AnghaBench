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
struct TYPE_3__ {scalar_t__* actext; int /*<<< orphan*/  id; int /*<<< orphan*/  label; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * CONVERT_TO_UTF8 (scalar_t__*) ; 
 int /*<<< orphan*/  CONVERT_TO_UTF8_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_IS_MENU_BAR (int /*<<< orphan*/ *) ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  gtk_box_pack_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_label_new (char const*) ; 
 int /*<<< orphan*/  gtk_label_new_with_mnemonic (char const*) ; 
 int /*<<< orphan*/  gtk_menu_item_new () ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ ) ; 
 char* p_wak ; 
 int /*<<< orphan*/ * translate_mnemonic_tag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
menu_item_new(vimmenu_T *menu, GtkWidget *parent_widget)
{
    GtkWidget	*box;
    char_u	*text;
    int		use_mnemonic;

    /* It would be neat to have image menu items, but that would require major
     * changes to Vim's menu system.  Not to mention that all the translations
     * had to be updated. */
    menu->id = gtk_menu_item_new();
    box = gtk_hbox_new(FALSE, 20);

    use_mnemonic = (p_wak[0] != 'n' || !GTK_IS_MENU_BAR(parent_widget));
    text = translate_mnemonic_tag(menu->name, use_mnemonic);

    menu->label = gtk_label_new_with_mnemonic((const char *)text);
    vim_free(text);

    gtk_box_pack_start(GTK_BOX(box), menu->label, FALSE, FALSE, 0);

    if (menu->actext != NULL && menu->actext[0] != NUL)
    {
	text = CONVERT_TO_UTF8(menu->actext);

	gtk_box_pack_end(GTK_BOX(box),
			 gtk_label_new((const char *)text),
			 FALSE, FALSE, 0);

	CONVERT_TO_UTF8_FREE(text);
    }

    gtk_container_add(GTK_CONTAINER(menu->id), box);
    gtk_widget_show_all(menu->id);
}