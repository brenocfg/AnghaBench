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
struct winedbg_arm_insn {void* str_asm; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cond (int) ; 
 size_t get_nibble (int,int) ; 
 void* r_str_appendf (void*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_mul(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short accu = (inst >> 21) & 0x01;
	short condcodes = (inst >> 20) & 0x01;

	if (accu) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mla%s%s %s, %s, %s, %s", get_cond (inst), condcodes ? "s" : "",
				tbl_regs[get_nibble (inst, 4)], tbl_regs[get_nibble (inst, 0)],
				tbl_regs[get_nibble (inst, 2)], tbl_regs[get_nibble (inst, 3)]);
	}
	else {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mul%s%s %s, %s, %s", get_cond (inst), condcodes ? "s" : "",
				tbl_regs[get_nibble (inst, 4)], tbl_regs[get_nibble (inst, 0)],
				tbl_regs[get_nibble (inst, 2)]);
	}
	return 0;
}