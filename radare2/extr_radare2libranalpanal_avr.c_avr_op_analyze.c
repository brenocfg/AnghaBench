#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  void* ut64 ;
typedef  int ut16 ;
struct TYPE_9__ {int mask; int selector; int cycles; int size; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ *,TYPE_1__*,int const*,int,int*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int cycles; int size; int nopcode; int /*<<< orphan*/  esil; void* val; void* ptr; void* jump; void* fail; void* addr; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;
typedef  TYPE_2__ OPCODE_DESC ;
typedef  int /*<<< orphan*/  CPU_MODEL ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_UNKNOWN ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UNK ; 
 void* UT64_MAX ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* opcodes ; 
 char* r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int const*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPCODE_DESC* avr_op_analyze(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, CPU_MODEL *cpu) {
	OPCODE_DESC *opcode_desc;
	if (len < 2) {
		return NULL;
	}
	ut16 ins = (buf[1] << 8) | buf[0];
	int fail;
	char *t;

	// initialize op struct
	memset (op, 0, sizeof (RAnalOp));
	op->ptr = UT64_MAX;
	op->val = UT64_MAX;
	op->jump = UT64_MAX;
	r_strbuf_init (&op->esil);

	// process opcode
	for (opcode_desc = opcodes; opcode_desc->handler; opcode_desc++) {
		if ((ins & opcode_desc->mask) == opcode_desc->selector) {
			fail = 0;

			// copy default cycles/size values
			op->cycles = opcode_desc->cycles;
			op->size = opcode_desc->size;
			op->type = opcode_desc->type;
			op->jump = UT64_MAX;
			op->fail = UT64_MAX;
			// op->fail = addr + op->size;
			op->addr = addr;

			// start void esil expression
			r_strbuf_setf (&op->esil, "");

			// handle opcode
			opcode_desc->handler (anal, op, buf, len, &fail, cpu);
			if (fail) {
				goto INVALID_OP;
			}
			if (op->cycles <= 0) {
				// eprintf ("opcode %s @%"PFMT64x" returned 0 cycles.\n", opcode_desc->name, op->addr);
				opcode_desc->cycles = 2;
			}
			op->nopcode = (op->type == R_ANAL_OP_TYPE_UNK);

			// remove trailing coma (COMETE LA COMA)
			t = r_strbuf_get (&op->esil);
			if (t && strlen (t) > 1) {
				t += strlen (t) - 1;
				if (*t == ',') {
					*t = '\0';
				}
			}

			return opcode_desc;
		}
	}

	// ignore reserved opcodes (if they have not been caught by the previous loop)
	if ((ins & 0xff00) == 0xff00 && (ins & 0xf) > 7) {
		goto INVALID_OP;
	}

INVALID_OP:
	// An unknown or invalid option has appeared.
	//  -- Throw pokeball!
	op->family = R_ANAL_OP_FAMILY_UNKNOWN;
	op->type = R_ANAL_OP_TYPE_UNK;
	op->addr = addr;
	op->fail = UT64_MAX;
	op->jump = UT64_MAX;
	op->ptr = UT64_MAX;
	op->val = UT64_MAX;
	op->nopcode = 1;
	op->cycles = 1;
	op->size = 2;
	// launch esil trap (for communicating upper layers about this weird
	// and stinky situation
	r_strbuf_set (&op->esil, "1,$");

	return NULL;
}