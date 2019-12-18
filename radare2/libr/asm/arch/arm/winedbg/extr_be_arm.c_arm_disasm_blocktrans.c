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
 void* r_str_appendf (void*,char*,char*,...) ; 
 int /*<<< orphan*/ * tbl_addrmode ; 
 char** tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_blocktrans(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short load      = (inst >> 20) & 0x01;
	short writeback = (inst >> 21) & 0x01;
	short psr       = (inst >> 22) & 0x01;
	short addrmode  = (inst >> 23) & 0x03;
	short i;
	short last=15;

	for (i=15;i>=0;i--) {
		if ((inst>>i) & 1) {
			last = i;
			break;
		}
	}

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s%s%s %s%s, {", load ? "ldm" : "stm", tbl_addrmode[addrmode],
			get_cond (inst), tbl_regs[get_nibble (inst, 4)], writeback ? "!" : "");
	for (i=0;i<=15;i++) {
		if ((inst>>i) & 1) {
			if (i == last) {
				arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s", tbl_regs[i]);
			} else {
				arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s, ", tbl_regs[i]);
			}
		}
	}
	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "}%s", psr ? "^" : "");
	return 0;
}