#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const ut8 ;
struct winedbg_arm_insn {int dummy; } ;
struct TYPE_7__ {int bits; scalar_t__ big_endian; int /*<<< orphan*/  pc; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int arm_disasm_one_insn (struct winedbg_arm_insn*) ; 
 int /*<<< orphan*/  arm_free (struct winedbg_arm_insn*) ; 
 struct winedbg_arm_insn* arm_new () ; 
 int /*<<< orphan*/  arm_set_input_buffer (struct winedbg_arm_insn*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  arm_set_pc (struct winedbg_arm_insn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_set_thumb (struct winedbg_arm_insn*,int) ; 
 int /*<<< orphan*/  r_asm_op_set_hex (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_mem_swapendian (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char const*) ; 
 char* winedbg_arm_insn_asm (struct winedbg_arm_insn*) ; 
 int /*<<< orphan*/  winedbg_arm_insn_hex (struct winedbg_arm_insn*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	ut8 buf2[4];
	struct winedbg_arm_insn *arminsn = arm_new();
	arm_set_pc (arminsn, a->pc);
	arm_set_thumb (arminsn, a->bits == 16);
	if (a->big_endian && a->bits == 32) {
		r_mem_swapendian (buf2, buf, 4);
		arm_set_input_buffer (arminsn, buf2);
	} else {
		arm_set_input_buffer (arminsn, buf);
	}
	op->size = arm_disasm_one_insn (arminsn);
	const char *asmstr = winedbg_arm_insn_asm (arminsn);
	if (asmstr) {
		r_strbuf_set (&op->buf_asm, asmstr);
		r_asm_op_set_hex(op, winedbg_arm_insn_hex (arminsn));
	} else {
		r_strbuf_set (&op->buf_asm, "invalid");
		r_strbuf_set (&op->buf, "");
	}
	arm_free (arminsn);
	return op->size;
}