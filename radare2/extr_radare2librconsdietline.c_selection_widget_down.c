#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sel_widget; } ;
struct TYPE_3__ {scalar_t__ selection; scalar_t__ scroll; } ;
typedef  TYPE_1__ RSelWidget ;

/* Variables and functions */
 TYPE_2__ I ; 
 void* R_MAX (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selection_widget_down(int steps) {
	RSelWidget *sel_widget = I.sel_widget;
	if (sel_widget) {
		sel_widget->selection = R_MAX (sel_widget->selection - steps, 0);
		if (steps == 1) {
			sel_widget->scroll = R_MAX (sel_widget->scroll - 1, 0);
		} else if (sel_widget->selection - sel_widget->scroll <= 0) {
			sel_widget->scroll = sel_widget->selection;
		}
	}
}