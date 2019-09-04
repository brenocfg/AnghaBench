#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  config; TYPE_1__* print; } ;
struct TYPE_5__ {scalar_t__ cur_enabled; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __core_visual_step_over(RCore *core) {
	bool io_cache = r_config_get_i (core->config, "io.cache");
	r_config_set_i (core->config, "io.cache", false);
	if (r_config_get_i (core->config, "cfg.debug")) {
		if (core->print->cur_enabled) {
			r_core_cmd (core, "dcr", 0);
			core->print->cur_enabled = 0;
		} else {
			r_core_cmd (core, "dso", 0);
			r_core_cmd (core, ".dr*", 0);
		}
	} else {
		r_core_cmd (core, "aeso", 0);
		r_core_cmd (core, ".ar*", 0);
	}
	r_config_set_i (core->config, "io.cache", io_cache);
}