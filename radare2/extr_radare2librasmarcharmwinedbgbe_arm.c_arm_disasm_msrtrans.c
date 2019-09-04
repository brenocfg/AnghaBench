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
 int /*<<< orphan*/  ROR32 (int,int) ; 
 int /*<<< orphan*/  get_cond (int) ; 
 int get_nibble (int,int) ; 
 void* r_str_appendf (void*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_msrtrans(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short immediate = (inst >> 25) & 0x01;
	short dst = (inst >> 22) & 0x01;
	short simple = (inst >> 16) & 0x01;

	if (simple || !immediate) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "msr%s %s, %s", get_cond (inst), dst ? "spsr" : "cpsr",
				tbl_regs[get_nibble (inst, 0)]);
		return 0;
	}
	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "msr%s %s, #%u", get_cond (inst), dst ? "spsr" : "cpsr",
			ROR32 (inst & 0xff, 2 * get_nibble (inst, 2)));
	return 0;
}