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
struct TYPE_6__ {int /*<<< orphan*/  config; int /*<<< orphan*/  assembler; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  r_asm_set_cpu (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rasm2_list (TYPE_1__*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  update_asmcpu_options (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static bool cb_asmcpu(void *user, void *data) {
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	if (*node->value == '?') {
		update_asmcpu_options (core, node);
		/* print verbose help instead of plain option listing */
		rasm2_list (core, r_config_get (core->config, "asm.arch"), node->value[1]);
		return 0;
	}
	r_asm_set_cpu (core->assembler, node->value);
	r_config_set (core->config, "anal.cpu", node->value);
	return true;
}