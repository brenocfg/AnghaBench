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
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __set_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __show_status (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 

int __io_cache_on_cb(void *user) {
	RCore *core = (RCore *)user;
	r_config_set_i (core->config, "io.cache", 1);
	(void)__show_status (core, "io.cache is on");
	__set_mode (core, PANEL_MODE_DEFAULT);
	return 0;
}