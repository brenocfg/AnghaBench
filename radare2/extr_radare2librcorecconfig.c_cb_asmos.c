#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  syscall; } ;
struct TYPE_7__ {char* value; } ;
struct TYPE_6__ {TYPE_4__* anal; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  R_SYS_OS ; 
 int /*<<< orphan*/  __setsegoff (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_node_options (TYPE_2__*) ; 
 int /*<<< orphan*/  r_anal_set_os (TYPE_4__*,char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* r_config_node_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_syscall_setup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cb_asmos(void *user, void *data) {
	RCore *core = (RCore*) user;
	int asmbits = r_config_get_i (core->config, "asm.bits");
	RConfigNode *asmarch, *node = (RConfigNode*) data;

	if (*node->value == '?') {
		print_node_options (node);
		return 0;
	}
	if (!node->value[0]) {
		free (node->value);
		node->value = strdup (R_SYS_OS);
	}
	asmarch = r_config_node_get (core->config, "asm.arch");
	if (asmarch) {
		const char *asmcpu = r_config_get (core->config, "asm.cpu");
		r_syscall_setup (core->anal->syscall, asmarch->value, core->anal->bits, asmcpu, node->value);
		__setsegoff (core->config, asmarch->value, asmbits);
	}
	r_anal_set_os (core->anal, node->value);

	return true;
}