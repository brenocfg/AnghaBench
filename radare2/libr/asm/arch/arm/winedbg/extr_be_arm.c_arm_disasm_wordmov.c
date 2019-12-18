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
struct winedbg_arm_insn {int /*<<< orphan*/  str_asm; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cond (int) ; 
 int get_nibble (int,int) ; 
 int /*<<< orphan*/  r_str_appendf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_wordmov(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short top = (inst >> 22) & 0x01;

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "mov%s%s %s, #%u", top ? "t" : "w", get_cond (inst),
			tbl_regs[get_nibble (inst, 3)],
			(get_nibble (inst, 4) << 12) | (inst & 0x0fff));
	return 0;
}