#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * reg; } ;
struct TYPE_18__ {TYPE_9__* dbg; TYPE_5__* anal; TYPE_3__* cons; int /*<<< orphan*/  config; } ;
struct TYPE_17__ {int size; } ;
struct TYPE_16__ {int bits; int /*<<< orphan*/ * reg; TYPE_4__* cur; } ;
struct TYPE_15__ {scalar_t__ arch; } ;
struct TYPE_14__ {TYPE_2__* context; } ;
struct TYPE_12__ {char* creg; } ;
struct TYPE_13__ {TYPE_1__ pal; } ;
typedef  TYPE_6__ RRegItem ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_7__ RCore ;

/* Variables and functions */
 char* Color_BWHITE ; 
 int /*<<< orphan*/  R_REG_NAME_PC ; 
 int R_REG_TYPE_GPR ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int /*<<< orphan*/  r_core_debug_ri (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_reg_list (TYPE_9__*,int,int,int,char const*) ; 
 TYPE_6__* r_reg_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* r_reg_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void __anal_reg_list(RCore *core, int type, int bits, char mode) {
	if (mode == 'i') {
		r_core_debug_ri (core, core->anal->reg, 0);
		return;
	}
	RReg *hack = core->dbg->reg;
	const char *use_color;
	int use_colors = r_config_get_i (core->config, "scr.color");
	if (use_colors) {
#undef ConsP
#define ConsP(x) (core->cons && core->cons->context->pal.x)? core->cons->context->pal.x
		use_color = ConsP (creg) : Color_BWHITE;
	} else {
		use_color = NULL;
	}
	if (bits < 0) {
		// TODO Change the `size` argument of r_debug_reg_list to use -1 for any and 0 for anal->bits
		bits = 0;
	} else if (!bits) {
		bits = core->anal->bits;
	}
	int mode2 = mode;
	if (core->anal) {
		core->dbg->reg = core->anal->reg;
		if (core->anal->cur && core->anal->cur->arch) {
			/* workaround for thumb */
			if (!strcmp (core->anal->cur->arch, "arm") && bits == 16) {
				bits = 32;
			}
			/* workaround for 6502 */
			if (!strcmp (core->anal->cur->arch, "6502") && bits == 8) {
				mode2 = mode == 'j' ? 'J' : mode;
				if (mode == 'j') {
					r_cons_printf ("{");
				}
				r_debug_reg_list (core->dbg, R_REG_TYPE_GPR, 16, mode2, use_color); // XXX detect which one is current usage
				if (mode == 'j') {
					r_cons_printf (",");
				}
			}
			if (!strcmp (core->anal->cur->arch, "avr") && bits == 8) {
				mode2 = mode == 'j' ? 'J' : mode;
				if (mode == 'j') {
					r_cons_printf ("{");
				}
				r_debug_reg_list (core->dbg, R_REG_TYPE_GPR, 16, mode2, use_color); // XXX detect which one is current usage
				if (mode == 'j') {
					r_cons_printf (",");
				}
			}
		}
	}

	if (mode == '=') {
		int pcbits = 0;
		const char *pcname = r_reg_get_name (core->anal->reg, R_REG_NAME_PC);
		RRegItem *reg = r_reg_get (core->anal->reg, pcname, 0);
		if (bits != reg->size) {
			pcbits = reg->size;
		}
		if (pcbits) {
			r_debug_reg_list (core->dbg, R_REG_TYPE_GPR, pcbits, 2, use_color); // XXX detect which one is current usage
		}
	}
	r_debug_reg_list (core->dbg, type, bits, mode2, use_color);
	if (mode2 == 'J') {
		r_cons_print ("}\n");
	}
	core->dbg->reg = hack;
}