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
 void* r_str_appendf (void*,char*,...) ; 
 short* tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_halfwordtrans(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short halfword  = (inst >> 5)  & 0x01;
	short sign      = (inst >> 6)  & 0x01;
	short load      = (inst >> 20) & 0x01;
	short writeback = (inst >> 21) & 0x01;
	short immediate = (inst >> 22) & 0x01;
	short direction = (inst >> 23) & 0x01;
	short indexing  = (inst >> 24) & 0x01;
	short offset    = ((inst >> 4) & 0xf0) + (inst & 0x0f);

	if (!direction){
		offset *= -1;
	}

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s%s%s%s%s", load ? "ldr" : "str", sign ? "s" : "",
			halfword ? "h" : (sign ? "b" : ""), writeback ? "t" : "", get_cond (inst));
	arminsn->str_asm = r_str_appendf (arminsn->str_asm, " %s, ", tbl_regs[get_nibble (inst, 3)]);
	if (indexing) {
		if (immediate) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s, #%d]", tbl_regs[get_nibble (inst, 4)], offset);
		}
		else {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s, %s]", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)]);
		}
	} else {
		if (immediate) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s], #%d", tbl_regs[get_nibble (inst, 4)], offset);
		}
		else {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s], %s", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)]);
		}
	}
	return 0;
}