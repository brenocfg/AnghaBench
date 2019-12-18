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
struct TYPE_4__ {int /*<<< orphan*/  ident; int /*<<< orphan*/  handler_id; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ scrollbar_T ;
struct TYPE_5__ {int /*<<< orphan*/  formwin; } ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_CAN_FOCUS ; 
 int /*<<< orphan*/  GTK_FORM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET_UNSET_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SBAR_HORIZ ; 
 int SBAR_VERT ; 
 int /*<<< orphan*/  adjustment_value_changed ; 
 int /*<<< orphan*/  gtk_form_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hscrollbar_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_range_get_adjustment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vscrollbar_new (int /*<<< orphan*/ *) ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/  gui_mch_update () ; 

void
gui_mch_create_scrollbar(scrollbar_T *sb, int orient)
{
    if (orient == SBAR_HORIZ)
	sb->id = gtk_hscrollbar_new(NULL);
    else if (orient == SBAR_VERT)
	sb->id = gtk_vscrollbar_new(NULL);

    if (sb->id != NULL)
    {
	GtkAdjustment *adjustment;

	GTK_WIDGET_UNSET_FLAGS(sb->id, GTK_CAN_FOCUS);
	gtk_form_put(GTK_FORM(gui.formwin), sb->id, 0, 0);

	adjustment = gtk_range_get_adjustment(GTK_RANGE(sb->id));

	sb->handler_id = gtk_signal_connect(
			     GTK_OBJECT(adjustment), "value_changed",
			     GTK_SIGNAL_FUNC(adjustment_value_changed),
			     GINT_TO_POINTER(sb->ident));
	gui_mch_update();
    }
}