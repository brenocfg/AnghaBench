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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __panel_single_step_over (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __update_disassembly_or_open (int /*<<< orphan*/ *) ; 

int __step_over_cb(void *user) {
	RCore *core = (RCore *)user;
	__panel_single_step_over (core);
	__update_disassembly_or_open (core);
	return 0;
}