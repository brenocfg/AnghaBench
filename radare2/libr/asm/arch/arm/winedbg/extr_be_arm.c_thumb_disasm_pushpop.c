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
struct winedbg_arm_insn {void* str_asm; } ;

/* Variables and functions */
 void* r_str_appendf (void*,char*,...) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut16 thumb_disasm_pushpop(struct winedbg_arm_insn *arminsn, ut16 inst) {
	short lrpc = (inst >> 8)  & 0x01;
	short load = (inst >> 11) & 0x01;
	short i;
	short last;

	for (i=7;i>=0;i--) {
		if ((inst>>i) & 1) {
			break;
		}
	}
	last = i;

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s {", load ? "pop" : "push");

	for (i=0;i<=7;i++) {
		if ((inst>>i) & 1) {
			if (i == last) {
				arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s", tbl_regs[i]);
			}
			else {
				arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s, ", tbl_regs[i]);
			}
		}
	}
	if (lrpc) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s%s", last ? ", " : "", load ? "pc" : "lr");
	}

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "}");
	return 0;
}