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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * CONVERT_TO_UTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONVERT_TO_UTF8_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ICON_SIZE_BUTTON ; 
 int /*<<< orphan*/ * gtk_alignment_new (float,float,float,float) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_image_new_from_stock (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_new (char const*) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkWidget *
create_image_button(const char *stock_id, const char *label)
{
    char_u	*text;
    GtkWidget	*box;
    GtkWidget	*alignment;
    GtkWidget	*button;

    text = CONVERT_TO_UTF8((char_u *)label);

    box = gtk_hbox_new(FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box),
		       gtk_image_new_from_stock(stock_id, GTK_ICON_SIZE_BUTTON),
		       FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box),
		       gtk_label_new((const char *)text),
		       FALSE, FALSE, 0);

    CONVERT_TO_UTF8_FREE(text);

    alignment = gtk_alignment_new((float)0.5, (float)0.5,
						      (float)0.0, (float)0.0);
    gtk_container_add(GTK_CONTAINER(alignment), box);
    gtk_widget_show_all(alignment);

    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), alignment);

    return button;
}