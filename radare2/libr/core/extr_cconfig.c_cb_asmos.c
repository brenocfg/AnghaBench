#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  syscall; } ;
struct TYPE_8__ {char* value; } ;
struct TYPE_7__ {TYPE_5__* anal; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  R_SYS_OS ; 
 int /*<<< orphan*/  __setsegoff (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_node_options (TYPE_2__*) ; 
 int /*<<< orphan*/  r_anal_set_os (TYPE_5__*,char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* r_config_node_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_core_anal_cc_init (TYPE_1__*) ; 
 int /*<<< orphan*/  r_syscall_setup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cb_asmos(void *user, void *data) {
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
	r_core_anal_cc_init (core);
	return true;
}