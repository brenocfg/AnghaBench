#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_11__ {int type; TYPE_1__* args; } ;
typedef  TYPE_2__ mcore_t ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ mcore_handle ;
struct TYPE_13__ {int type; int size; int eob; void* jump; void* fail; void* val; void* ptr; scalar_t__ delay; } ;
struct TYPE_10__ {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_4__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
#define  R_ANAL_OP_TYPE_CALL 133 
#define  R_ANAL_OP_TYPE_CJMP 132 
#define  R_ANAL_OP_TYPE_ICALL 131 
#define  R_ANAL_OP_TYPE_ILL 130 
#define  R_ANAL_OP_TYPE_JMP 129 
 int R_ANAL_OP_TYPE_NULL ; 
#define  R_ANAL_OP_TYPE_RET 128 
 void* UT64_MAX ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  mcore_free (TYPE_2__*) ; 
 scalar_t__ mcore_init (TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 TYPE_2__* mcore_next (TYPE_3__*) ; 

__attribute__((used)) static int mcore_anal(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	mcore_handle handle = {0};
	mcore_t* instr = NULL;

	if (mcore_init (&handle, buf, len)) {
		eprintf ("[!] mcore: bad or invalid data.\n");
		return -1;
	}

	op->delay = 0;
	op->type = R_ANAL_OP_TYPE_NULL;
	op->jump = UT64_MAX;
	op->fail = UT64_MAX;
	op->ptr = op->val = UT64_MAX;
	op->size = 2;
	if ((instr = mcore_next (&handle))) {
		op->type = instr->type;
		switch (instr->type) {
		case R_ANAL_OP_TYPE_CALL:
		case R_ANAL_OP_TYPE_CJMP:
			op->fail = addr + 2;
			op->jump = addr + instr->args[0].value + 1;
			break;
		case R_ANAL_OP_TYPE_JMP:
			op->jump = addr + instr->args[0].value + 1;
			break;
		case R_ANAL_OP_TYPE_ICALL:
			// the loading address depends on the word
			// that this pointer points to.
			// op->jump = addr + ((instr->args[i].value << 2) & 0xfffffffc);
			break;
		case R_ANAL_OP_TYPE_RET:
		case R_ANAL_OP_TYPE_ILL:
			op->eob = true;
			break;
		default:
			break;
		}
		mcore_free (instr);
	}
	return op->size;
}