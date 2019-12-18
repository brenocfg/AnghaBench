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
 void* r_str_appendf (void*,char*,char*,char*,size_t,int,int /*<<< orphan*/ ,size_t,size_t,...) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 thumb2_disasm_coprocmov1(struct winedbg_arm_insn *arminsn, ut32 inst) {
	ut16 opc1 = (inst >> 21) & 0x07;
	ut16 opc2 = (inst >> 5) & 0x07;

	if (opc2) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm,
				"%s%s\tp%u, #%u, %s, cr%u, cr%u, #%u", (inst & 0x00100000)?"mrc":"mcr",
				(inst & 0x10000000)?"2":"", get_nibble (inst, 2), opc1,
				tbl_regs[get_nibble (inst, 3)], get_nibble (inst, 4), get_nibble (inst, 0), opc2);
	}
	else {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm,
				"%s%s\tp%u, #%u, %s, cr%u, cr%u", (inst & 0x00100000)?"mrc":"mcr",
				(inst & 0x10000000)?"2":"", get_nibble (inst, 2), opc1,
				tbl_regs[get_nibble (inst, 3)], get_nibble (inst, 4), get_nibble (inst, 0));
	}
	return 0;
}