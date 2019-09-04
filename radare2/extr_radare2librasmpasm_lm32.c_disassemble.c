#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_10__ {int invhex; int /*<<< orphan*/  pc; } ;
struct TYPE_9__ {int value; int /*<<< orphan*/  addr; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsmLm32Instruction ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 scalar_t__ r_asm_lm32_decode (TYPE_2__*) ; 
 scalar_t__ r_asm_lm32_stringify (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	RAsmLm32Instruction instr = {0};
	instr.value = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
	instr.addr = a->pc;
	if (r_asm_lm32_decode (&instr)) {
		r_strbuf_set (&op->buf_asm, "invalid");
		a->invhex = 1;
		return -1;
	}
	//op->buf_asm is 256 chars long, which is more than sufficient
	if (r_asm_lm32_stringify (&instr, r_strbuf_get (&op->buf_asm))) {
		r_strbuf_set (&op->buf_asm, "invalid");
		a->invhex = 1;
		return -1;
	}
	return 4;
}