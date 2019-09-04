#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct riscv_opcode {int pinfo; int /*<<< orphan*/  name; scalar_t__* subset; } ;
struct TYPE_6__ {int bits; int /*<<< orphan*/  big_endian; } ;
struct TYPE_5__ {int size; int addr; int jump; int fail; void* type; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int EXTRACT_SBTYPE_IMM (int) ; 
 int EXTRACT_UJTYPE_IMM (int) ; 
 int INSN_ALIAS ; 
 size_t NUMOPCODES ; 
 int OP_MASK_RD ; 
 int OP_SH_RD ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOT ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_UCALL ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int UT64_MAX ; 
 int atoi (scalar_t__*) ; 
 struct riscv_opcode* get_opcode (int) ; 
 scalar_t__ is_any (char*,...) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int r_read_ble16 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int r_read_ble64 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct riscv_opcode* riscv_opcodes ; 

__attribute__((used)) static int riscv_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len, RAnalOpMask mask) {
	const int no_alias = 1;
	struct riscv_opcode *o = NULL;
	ut64 word = 0;
	int xlen = anal->bits;

	op->size = 4;
	op->addr = addr;
	op->type = R_ANAL_OP_TYPE_UNK;

	if (len >= sizeof (ut64)) {
		word = r_read_ble64 (data, anal->big_endian);
	} else if (len >= sizeof (ut32)) {
		word = r_read_ble16 (data, anal->big_endian);
	} else {
		op->type = R_ANAL_OP_TYPE_ILL;
		return -1;
	}

	o = get_opcode (word);
	if (word == UT64_MAX) {
		op->type = R_ANAL_OP_TYPE_ILL;
		return -1;
	}
	if (!o || !o->name) {
		return op->size;
	}

	for (; o < &riscv_opcodes[NUMOPCODES]; o++) {
		// XXX ASAN segfault if ( !(o->match_func)(o, word) ) continue;
		if (no_alias && (o->pinfo & INSN_ALIAS)) {
			continue;
		}
		if (isdigit ((ut8)(o->subset[0])) && atoi (o->subset) != xlen) {
			continue;
		} else {
			break;
		}
	}

	if (!o || !o->name) {
		return -1;
	}
// branch/jumps/calls/rets
	if (is_any ("jal")) {
		// decide wether it's ret or call
		int rd = (word >> OP_SH_RD) & OP_MASK_RD;
		op->type = (rd == 0) ? R_ANAL_OP_TYPE_RET: R_ANAL_OP_TYPE_CALL;
		op->jump = EXTRACT_UJTYPE_IMM (word) + addr;
		op->fail = addr + 4;
	} else if (is_any ("jr")) {
		op->type = R_ANAL_OP_TYPE_JMP;
	} else if (is_any ("j", "jump")) {
		op->type = R_ANAL_OP_TYPE_JMP;
	} else if (is_any ("jalr", "ret")) { // ?
		op->type = R_ANAL_OP_TYPE_UCALL;
	} else if (is_any ("ret")) {
		op->type = R_ANAL_OP_TYPE_RET;
	} else if (is_any ("beqz", "beq", "blez", "bgez", "ble",
			"bleu", "bge", "bgeu", "bltz", "bgtz", "blt", "bltu",
			"bgt", "bgtu", "bnez", "bne")) {
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = EXTRACT_SBTYPE_IMM (word) + addr;
		op->fail = addr + 4;
// math
	} else if (is_any ("addi", "addw", "addiw", "add", "auipc")) {
		op->type = R_ANAL_OP_TYPE_ADD;
	} else if (is_any ("subi", "subw", "sub")) {
		op->type = R_ANAL_OP_TYPE_SUB;
	} else if (is_any ("xori", "xor")) {
		op->type = R_ANAL_OP_TYPE_XOR;
	} else if (is_any ("andi", "and")) {
		op->type = R_ANAL_OP_TYPE_AND;
	} else if (is_any ("ori", "or")) {
		op->type = R_ANAL_OP_TYPE_OR;
	} else if (is_any ("not")) {
		op->type = R_ANAL_OP_TYPE_NOT;
	} else if (is_any ("mul", "mulh", "mulhu", "mulhsu", "mulw")) {
		op->type = R_ANAL_OP_TYPE_MUL;
	} else if (is_any ("div", "divu", "divw", "divuw")) {
		op->type = R_ANAL_OP_TYPE_DIV;
// memory
	} else if (is_any ("sd", "sb", "sh", "sw")) {
		op->type = R_ANAL_OP_TYPE_STORE;
	} else if (is_any ("ld", "lw", "lwu", "lui", "li",
			"lb", "lbu", "lh", "lhu", "la", "lla")) {
		op->type = R_ANAL_OP_TYPE_LOAD;
	}
	return op->size;
}