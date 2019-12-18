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
struct TYPE_9__ {int op_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ amd29k_instr_t ;
struct TYPE_11__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_10__ {int type; int size; int eob; scalar_t__ delay; void* fail; void* jump; void* val; void* ptr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
#define  R_ANAL_OP_TYPE_CJMP 131 
#define  R_ANAL_OP_TYPE_ICALL 130 
#define  R_ANAL_OP_TYPE_JMP 129 
 int R_ANAL_OP_TYPE_NULL ; 
#define  R_ANAL_OP_TYPE_RET 128 
 void* UT64_MAX ; 
 scalar_t__ amd29k_instr_decode (int /*<<< orphan*/  const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd29k_instr_is_ret (TYPE_1__*) ; 
 void* amd29k_instr_jump (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	op->delay = 0;
	op->type = R_ANAL_OP_TYPE_NULL;
	op->jump = op->fail = UT64_MAX;
	op->ptr = op->val = UT64_MAX;
	op->size = 4;
	op->eob = false;

	// delayed branch is bugged as hell. disabled for now.

	amd29k_instr_t instruction = {0};
	if (amd29k_instr_decode (buf, len, &instruction, a->cpu)) {
		op->type = instruction.op_type;
		switch (op->type) {
		case R_ANAL_OP_TYPE_JMP:
			op->jump = amd29k_instr_jump (addr, &instruction);
			//op->delay = 1;
			break;
		case R_ANAL_OP_TYPE_CJMP:
			op->jump = amd29k_instr_jump (addr, &instruction);
			op->fail = addr + 4;
			//op->delay = 1;
			break;
		case R_ANAL_OP_TYPE_ICALL:
			if (amd29k_instr_is_ret (&instruction)) {
				op->type = R_ANAL_OP_TYPE_RET;
				op->eob = true;
			}
			//op->delay = 1;
			break;
		case R_ANAL_OP_TYPE_RET:
			op->eob = true;
			//op->delay = 1;
			break;
		default:
			op->delay = 0;
			break;
		}
	}

	return op->size;
}