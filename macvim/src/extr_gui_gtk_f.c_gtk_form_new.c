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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkForm ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_form_get_type () ; 
 int /*<<< orphan*/ * gtk_type_new (int /*<<< orphan*/ ) ; 

GtkWidget *
gtk_form_new(void)
{
    GtkForm *form;

    form = gtk_type_new(gtk_form_get_type());

    return GTK_WIDGET(form);
}