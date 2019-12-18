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
 int get_cond (int) ; 
 size_t get_nibble (int,int) ; 
 void* r_str_appendf (void*,char*,char*,...) ; 
 char** tbl_regs ; 
 char** tbl_shifts ; 

__attribute__((used)) static ut32 arm_disasm_singletrans(struct winedbg_arm_insn *arminsn, ut32 inst) {
	short load      = (inst >> 20) & 0x01;
	short writeback = (inst >> 21) & 0x01;
	short byte      = (inst >> 22) & 0x01;
	short direction = (inst >> 23) & 0x01;
	short indexing  = (inst >> 24) & 0x01;
	short immediate = !((inst >> 25) & 0x01);
	short offset    = inst & 0x0fff;

	if (!direction) {
		offset *= -1;
	}

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s%s%s%s", load ? "ldr" : "str", byte ? "b" : "", writeback ? "t" : "",
			get_cond (inst));
	arminsn->str_asm = r_str_appendf (arminsn->str_asm, " %s, ", tbl_regs[get_nibble (inst, 3)]);
	if (indexing) {
		if (immediate) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s, #%d]", tbl_regs[get_nibble (inst, 4)], offset);
		}
		else if (((inst >> 4) & 0xff) == 0x00) { /* no shift */
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s, %s]", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)]);
		}
		else if (((inst >> 4) & 0x01) == 0x00) {/* immediate shift (there's no register shift) */
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s, %s, %s #%d]", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)], tbl_shifts[(inst >> 5) & 0x03],
					(inst >> 7) & 0x1f);
		}
		else {
			return inst;
		}
	} else {
		if (immediate) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s], #%d", tbl_regs[get_nibble (inst, 4)], offset);
		}
		else if (((inst >> 4) & 0xff) == 0x00) { /* no shift */
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s], %s", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)]);
		}
		else if (((inst >> 4) & 0x01) == 0x00) { /* immediate shift (there's no register shift) */
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "[%s], %s, %s #%d", tbl_regs[get_nibble (inst, 4)],
					tbl_regs[get_nibble (inst, 0)], tbl_shifts[(inst >> 5) & 0x03],
					(inst >> 7) & 0x1f);
		}
		else {
			return inst;
		}
	}
	return 0;
}