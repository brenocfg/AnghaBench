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
struct TYPE_2__ {int /*<<< orphan*/  drawarea; int /*<<< orphan*/  formwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_FORM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_form_move_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 TYPE_1__ gui ; 

void
gui_mch_set_text_area_pos(int x, int y, int w, int h)
{
    gtk_form_move_resize(GTK_FORM(gui.formwin), gui.drawarea, x, y, w, h);
}