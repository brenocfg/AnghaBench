#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut16 ;
typedef  int uint8_t ;
typedef  void* uint16_t ;
struct TYPE_4__ {int size; void* type; int /*<<< orphan*/  fail; void* jump; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_RJMP ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  R_META_TYPE_COMMENT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  r_meta_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int r_read_be16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int chip8_anop(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len, RAnalOpMask mask) {
	memset (op, '\0', sizeof (RAnalOp));
	ut16 opcode = r_read_be16 (data);
//	uint8_t x = (opcode >> 8) & 0x0F;
//	uint8_t y = (opcode >> 4) & 0x0F;
	uint8_t nibble = opcode & 0x0F;
	uint16_t nnn = opcode & 0x0FFF;
	uint8_t kk = opcode & 0xFF;
	op->size = 2;
	op->addr = addr;
	op->type = R_ANAL_OP_TYPE_UNK;
	switch (opcode & 0xF000) {
	case 0x0000:
		if (opcode == 0x00EE) {
			op->type = R_ANAL_OP_TYPE_RET;
		}
		break;
	case 0x1000:
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = nnn;
		break;
	case 0x2000:
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = nnn;
		break;
	case 0x3000:
		op->type = R_ANAL_OP_TYPE_RJMP;
		op->jump = addr + op->size * 2;
		op->fail = addr + op->size;
		break;
	case 0x4000:
		op->type = R_ANAL_OP_TYPE_RJMP;
		op->jump = addr + op->size * 2;
		op->fail = addr + op->size;
		break;
	case 0x5000:
		op->type = R_ANAL_OP_TYPE_RJMP;
		op->jump = addr + op->size * 2;
		op->fail = addr + op->size;
		break;
	case 0x6000:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 0x7000:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 0x8000: {
		switch (nibble) {
		case 0x0:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x1:
			op->type = R_ANAL_OP_TYPE_OR;
			break;
		case 0x2:
			op->type = R_ANAL_OP_TYPE_AND;
			break;
		case 0x3:
			op->type = R_ANAL_OP_TYPE_XOR;
			break;
		case 0x4:
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x5:
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case 0x6:
			op->type = R_ANAL_OP_TYPE_SHR;
			break;
		case 0x7:
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case 0xE:
			op->type = R_ANAL_OP_TYPE_SHL;
			break;
		}
	} break;
	case 0x9000:
		if (nibble == 0) {
			op->type = R_ANAL_OP_TYPE_RJMP;
			op->jump = addr + op->size * 2;
			op->fail = addr + op->size;
		}
		break;
	case 0xA000:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 0xB000:
		op->type = R_ANAL_OP_TYPE_JMP;
		/* FIXME: this is wrong as op->jump depends on register V0 */
		op->jump = nnn;
		break;
	case 0xE000:
		if (kk == 0x9E || kk == 0xA1) {
			r_meta_set_string (anal, R_META_TYPE_COMMENT, addr, "KEYPAD");
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = addr + op->size * 2;
			op->fail = addr + op->size;
		}
		break;
	case 0xF000: {
		switch (kk) {
		case 0x07:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x0A:
			r_meta_set_string (anal, R_META_TYPE_COMMENT, addr, "KEYPAD");
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x15:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x18:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x1E:
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x29:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x30:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x33:
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x55:
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x65:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x75:
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x85:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		}
	} break;
	}
	return op->size;
}