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
 int /*<<< orphan*/  get_cond (int) ; 
 size_t get_nibble (int,int) ; 
 void* r_str_appendf (void*,char*,...) ; 
 int /*<<< orphan*/ * tbl_regs ; 

__attribute__((used)) static ut32 arm_disasm_coprocdatatrans(struct winedbg_arm_insn *arminsn, ut32 inst) {
	ut16 CPnum  = (inst >> 8)  & 0x0f;
	ut16 CRd    = (inst >> 12) & 0x0f;
	ut16 load      = (inst >> 20) & 0x01;
	ut16 writeback = (inst >> 21) & 0x01;
	ut16 translen  = (inst >> 22) & 0x01;
	ut16 direction = (inst >> 23) & 0x01;
	ut16 indexing  = (inst >> 24) & 0x01;
	short offset    = (inst & 0xff) << 2;

	if (!direction) {
		offset *= -1;
	}

	arminsn->str_asm = r_str_appendf (arminsn->str_asm, "%s%s%s", load ? "ldc" : "stc", translen ? "l" : "", get_cond (inst));
	if (indexing) {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, " %u, cr%u, [%s, #%d]%s", CPnum, CRd, tbl_regs[get_nibble (inst, 4)],
			offset, writeback ? "!" : "");
	} else {
		arminsn->str_asm = r_str_appendf (arminsn->str_asm, " %u, cr%u, [%s], #%d", CPnum, CRd, tbl_regs[get_nibble (inst, 4)],
			offset);
	}
	return 0;
}