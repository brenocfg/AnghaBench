#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* anal; int /*<<< orphan*/  config; } ;
struct TYPE_4__ {int /*<<< orphan*/ * esil; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  RConfigHold ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_NAME_BP ; 
 int /*<<< orphan*/  R_REG_NAME_SP ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_config_hold_i (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_getv (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool r_anal_emul_init(RCore *core, RConfigHold *hc) {
	r_config_hold_i (hc, "esil.romem", "asm.trace", "dbg.trace",
			"esil.nonull", "dbg.follow", NULL);
	r_config_set (core->config, "esil.romem", "true");
	r_config_set (core->config, "asm.trace", "true");
	r_config_set (core->config, "dbg.trace", "true");
	r_config_set (core->config, "esil.nonull", "true");
	r_config_set_i (core->config, "dbg.follow", false);
	const char *bp = r_reg_get_name (core->anal->reg, R_REG_NAME_BP);
	const char *sp = r_reg_get_name (core->anal->reg, R_REG_NAME_SP);
	if ((bp && !r_reg_getv (core->anal->reg, bp)) && (sp && !r_reg_getv (core->anal->reg, sp))) {
		eprintf ("Stack isn't initialized.\n");
		eprintf ("Try running aei and aeim commands before aft for default stack initialization\n");
		return false;
	}
	return (core->anal->esil != NULL);
}