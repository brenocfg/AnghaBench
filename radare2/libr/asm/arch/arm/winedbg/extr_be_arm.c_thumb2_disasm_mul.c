#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ut32 ;
typedef  int ut16 ;
struct winedbg_arm_insn {void* str_asm; } ;

/* Variables and functions */
 size_t get_nibble (int,int) ; 
 void* r_str_appendf (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 thumb2_disasm_mul(struct winedbg_arm_insn *arminsn, ut32 inst) {
	ut16 op1 = (inst >> 20) & 0x07;
	ut16 op2 = (inst >> 4) & 0x03;

	if (op1) {
		return inst;
	}

	if (op2 == 0 && get_nibble (inst, 3) != 0xf) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mla %s, %s, %s, %s ", tbl_regs[get_nibble (inst, 2)],
				tbl_regs[get_nibble (inst, 4)],
				tbl_regs[get_nibble (inst, 0)],
				tbl_regs[get_nibble (inst, 3)]);
		return 0;
	}

	if (op2 == 0 && get_nibble (inst, 3) == 0xf) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mul %s, %s, %s ", tbl_regs[get_nibble (inst, 2)],
				tbl_regs[get_nibble (inst, 4)],
				tbl_regs[get_nibble (inst, 0)]);
		return 0;
	}

	if (op2 == 1) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mls %s, %s, %s, %s ", tbl_regs[get_nibble (inst, 2)],
				tbl_regs[get_nibble (inst, 4)],
				tbl_regs[get_nibble (inst, 0)],
				tbl_regs[get_nibble (inst, 3)]);
		return 0;
	}

	return inst;
}