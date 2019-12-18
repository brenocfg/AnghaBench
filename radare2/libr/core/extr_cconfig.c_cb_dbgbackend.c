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
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbg; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_debug_plugin_list (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  r_debug_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool cb_dbgbackend(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (!strcmp (node->value, "?")) {
		r_debug_plugin_list (core->dbg, 'q');
		return false;
	}
	if (!strcmp (node->value, "bf")) {
		// hack
		r_config_set (core->config, "asm.arch", "bf");
	}
	r_debug_use (core->dbg, node->value);
	return true;
}