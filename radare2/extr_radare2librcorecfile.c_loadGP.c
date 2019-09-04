#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_10__ {int /*<<< orphan*/  config; TYPE_1__* anal; int /*<<< orphan*/  num; TYPE_3__* assembler; } ;
struct TYPE_9__ {TYPE_2__* cur; } ;
struct TYPE_8__ {int /*<<< orphan*/  arch; } ;
struct TYPE_7__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_4__*,char*) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_reg_getv (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void loadGP(RCore *core) {
	if (strstr (core->assembler->cur->arch, "mips")) {
		ut64 gp = r_num_math (core->num, "loc._gp");
		if (!gp || gp == UT64_MAX) {
			r_config_set (core->config, "anal.roregs", "zero");
			r_core_cmd0 (core, "10aes@entry0");
			r_config_set (core->config, "anal.roregs", "zero,gp");
			gp = r_reg_getv (core->anal->reg, "gp");
		}
		// eprintf ("[mips] gp: 0x%08"PFMT64x"\n", gp);
		r_config_set_i (core->config, "anal.gp", gp);
	}
}