#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* value; } ;
struct TYPE_6__ {int /*<<< orphan*/  config; int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  print_node_options (TYPE_2__*) ; 
 scalar_t__ r_anal_use (int /*<<< orphan*/ ,char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  update_analarch_options (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static bool cb_analarch(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (*node->value == '?') {
		update_analarch_options (core, node);
		print_node_options (node);
		return false;
	}
	if (*node->value) {
		if (r_anal_use (core->anal, node->value)) {
			return true;
		}
		const char *aa = r_config_get (core->config, "asm.arch");
		if (!aa || strcmp (aa, node->value)) {
			eprintf ("anal.arch: cannot find '%s'\n", node->value);
		} else {
			r_config_set (core->config, "anal.arch", "null");
			return true;
		}
	}
	return false;
}