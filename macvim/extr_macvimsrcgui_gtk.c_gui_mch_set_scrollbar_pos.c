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
struct TYPE_4__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ scrollbar_T ;
struct TYPE_5__ {int /*<<< orphan*/  formwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_FORM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_form_move_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 
 TYPE_3__ gui ; 

void
gui_mch_set_scrollbar_pos(scrollbar_T *sb, int x, int y, int w, int h)
{
    if (sb->id != NULL)
	gtk_form_move_resize(GTK_FORM(gui.formwin), sb->id, x, y, w, h);
}