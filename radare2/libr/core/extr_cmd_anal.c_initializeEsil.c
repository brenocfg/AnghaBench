#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_15__ {int /*<<< orphan*/  reg; TYPE_4__* esil; } ;
struct TYPE_14__ {int exectrap; void* cmd_step_out; void* cmd_step; int /*<<< orphan*/  cmd; void* verbose; } ;
struct TYPE_13__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct TYPE_12__ {scalar_t__ has_va; } ;
struct TYPE_11__ {TYPE_8__* anal; int /*<<< orphan*/  offset; int /*<<< orphan*/  bin; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinInfo ;
typedef  TYPE_3__ RBinAddr ;
typedef  TYPE_4__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_NAME_PC ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__* r_anal_esil_new (int,int,unsigned int) ; 
 int /*<<< orphan*/  r_anal_esil_setup (TYPE_4__*,TYPE_8__*,int,int,int) ; 
 int /*<<< orphan*/ * r_bin_get_entries (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_bin_get_info (int /*<<< orphan*/ ) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 void* r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_core_esil_cmd ; 
 int /*<<< orphan*/  r_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_push (int /*<<< orphan*/ *,TYPE_3__*) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_setv (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static ut64 initializeEsil(RCore *core) {
	const char *name = r_reg_get_name (core->anal->reg, R_REG_NAME_PC);
	int romem = r_config_get_i (core->config, "esil.romem");
	int stats = r_config_get_i (core->config, "esil.stats");
	int iotrap = r_config_get_i (core->config, "esil.iotrap");
	int exectrap = r_config_get_i (core->config, "esil.exectrap");
	int stacksize = r_config_get_i (core->config, "esil.stack.depth");
	int noNULL = r_config_get_i (core->config, "esil.noNULL");
	unsigned int addrsize = r_config_get_i (core->config, "esil.addr.size");
	if (!(core->anal->esil = r_anal_esil_new (stacksize, iotrap, addrsize))) {
		return UT64_MAX;
	}
	ut64 addr;
	RAnalEsil *esil = core->anal->esil;
	esil->verbose = r_config_get_i (core->config, "esil.verbose");
	esil->cmd = r_core_esil_cmd;
	r_anal_esil_setup (esil, core->anal, romem, stats, noNULL); // setup io
	{
		const char *cmd_esil_step = r_config_get (core->config, "cmd.esil.step");
		if (cmd_esil_step && *cmd_esil_step) {
			esil->cmd_step = strdup (cmd_esil_step);
		}
		const char *cmd_esil_step_out = r_config_get (core->config, "cmd.esil.stepout");
		if (cmd_esil_step_out && *cmd_esil_step_out) {
			esil->cmd_step_out = strdup (cmd_esil_step_out);
		}
		{
			const char *s = r_config_get (core->config, "cmd.esil.intr");
			if (s) {
				char *my = strdup (s);
				if (my) {
					r_config_set (core->config, "cmd.esil.intr", my);
					free (my);
				}
			}
		}
	}
	esil->exectrap = exectrap;
	RList *entries = r_bin_get_entries (core->bin);
	RBinAddr *entry = NULL;
	RBinInfo *info = NULL;
	if (entries && !r_list_empty (entries)) {
		entry = (RBinAddr *)r_list_pop (entries);
		info = r_bin_get_info (core->bin);
		addr = info->has_va? entry->vaddr: entry->paddr;
		r_list_push (entries, entry);
	} else {
		addr = core->offset;
	}
	r_reg_setv (core->anal->reg, name, addr);
	// set memory read only
	return addr;
}