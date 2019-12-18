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
struct TYPE_4__ {scalar_t__ i_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 scalar_t__ r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static bool cb_dbgstatus(void *user, void *data) {
	RCore *r = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (r_config_get_i (r->config, "cfg.debug")) {
		if (node->i_value) {
			r_config_set (r->config, "cmd.prompt",
				".dr*; drd; sr PC;pi 1;s-");
		} else {
			r_config_set (r->config, "cmd.prompt", ".dr*");
		}
	}
	return true;
}