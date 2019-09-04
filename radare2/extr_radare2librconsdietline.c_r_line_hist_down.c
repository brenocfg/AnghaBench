#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* cb_history_down ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_1__ I ; 
 int /*<<< orphan*/  r_line_hist_cmd_down ; 
 int /*<<< orphan*/  r_line_hist_cmd_up ; 
 int /*<<< orphan*/  r_line_set_hist_callback (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int r_line_hist_down() {
	if (!I.cb_history_down) {
		r_line_set_hist_callback (&I, &r_line_hist_cmd_up, &r_line_hist_cmd_down);
	}
	return I.cb_history_down (&I);
}