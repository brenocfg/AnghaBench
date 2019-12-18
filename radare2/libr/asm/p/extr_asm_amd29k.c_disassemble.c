#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  buf_asm ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ amd29k_instr_t ;
struct TYPE_11__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  pc; } ;
struct TYPE_10__ {int size; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 scalar_t__ amd29k_instr_decode (int /*<<< orphan*/  const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd29k_instr_print (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	if (!a || !op || !buf || len < 4) {
		return -1;
	}
	char buf_asm[64];
	ut64 offset = a->pc;
	amd29k_instr_t instruction = {0};
	op->size = 4;
	if (amd29k_instr_decode (buf, len, &instruction, a->cpu)) {
		amd29k_instr_print (buf_asm, sizeof (buf_asm), offset, &instruction);
		r_asm_op_set_asm (op, buf_asm);
		return 4;
	}
	r_asm_op_set_asm (op, "invalid");
	return -1;
}