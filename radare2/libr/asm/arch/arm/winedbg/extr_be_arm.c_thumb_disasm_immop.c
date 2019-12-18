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
typedef  int ut16 ;
struct winedbg_arm_insn {int /*<<< orphan*/  str_asm; } ;

/* Variables and functions */
 int /*<<< orphan*/  r_str_appendf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tbl_immops_t ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut16 thumb_disasm_immop(struct winedbg_arm_insn *arminsn, ut16 inst) {
	ut16 op = (inst >> 11) & 0x03;
	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s %s, #%u", tbl_immops_t[op], tbl_regs[(inst >> 8) & 0x07],
			inst & 0xff);
	return 0;
}