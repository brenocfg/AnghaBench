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
struct TYPE_5__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __esil_step_to (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_1__*,int,int) ; 
 char* __show_status_input (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,char*) ; 

int __esil_step_to_cb(void *user) {
	RCore *core = (RCore *)user;
	char *end = __show_status_input (core, "target addr: ");
	__esil_step_to (core, r_num_math (core->num, end));
	__set_refresh_all (core, false, false);
	return 0;
}