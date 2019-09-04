#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  void* st8 ;
struct TYPE_53__ {int /*<<< orphan*/  type; } ;
struct TYPE_52__ {int /*<<< orphan*/  reg; } ;
struct TYPE_51__ {scalar_t__ type; int size; int nopcode; int cycles; int eob; int failcycles; int stackptr; int jump; void* stackop; int /*<<< orphan*/  esil; int /*<<< orphan*/  fail; void* type2; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SOFTCAST (size_t const,size_t const) ; 
 scalar_t__ R_ANAL_OP_TYPE_ACMP ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 scalar_t__ R_ANAL_OP_TYPE_CALL ; 
 scalar_t__ R_ANAL_OP_TYPE_CCALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 scalar_t__ R_ANAL_OP_TYPE_CRET ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 scalar_t__ R_ANAL_OP_TYPE_NOP ; 
 scalar_t__ R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_OR ; 
 scalar_t__ R_ANAL_OP_TYPE_POP ; 
 scalar_t__ R_ANAL_OP_TYPE_PUSH ; 
 scalar_t__ R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_ROL ; 
 void* R_ANAL_OP_TYPE_ROR ; 
 scalar_t__ R_ANAL_OP_TYPE_SAL ; 
 scalar_t__ R_ANAL_OP_TYPE_SAR ; 
 scalar_t__ R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 scalar_t__ R_ANAL_OP_TYPE_UCALL ; 
 scalar_t__ R_ANAL_OP_TYPE_UCCALL ; 
 scalar_t__ R_ANAL_OP_TYPE_UCJMP ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 scalar_t__ R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 void* R_ANAL_STACK_INC ; 
 int gbOpLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_anal_add_hl (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_add_sp (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_and_bit (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_and_res (TYPE_2__*,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_rl (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_rlc (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_rr (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_rrc (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_sla (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_sra (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_srl (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cb_swap (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_cond (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_esil_call (TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_esil_ccall (TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_esil_cjmp (TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_esil_cret (TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_esil_jmp (TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_esil_ret (TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_id (TYPE_2__*,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_jmp_hl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_load (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_load_hl (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_mov_hl_sp (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_mov_ime (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_mov_imm (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_mov_reg (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_mov_scf (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_mov_sp_hl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_or_set (TYPE_2__*,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_pp (int /*<<< orphan*/ ,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  gb_anal_store (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_store_hl (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_xoaasc (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_xoaasc_imm (int /*<<< orphan*/ ,TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  gb_anal_xor_ccf (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gb_anal_xor_cpl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_8__* gb_op ; 
 int /*<<< orphan*/  gb_op_calljump (TYPE_2__*,TYPE_1__*,size_t const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  meta_gb_bankswitch_cmt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meta_gb_hardware_cmt (TYPE_2__*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int gb_anop(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len, RAnalOpMask mask) {
	int ilen = gbOpLength (gb_op[data[0]].type);
	if (ilen > len) {
		ilen = 0;
	}
	memset (op, '\0', sizeof (RAnalOp));
	op->addr = addr;
	op->type = R_ANAL_OP_TYPE_UNK;
	op->size = ilen;
	op->nopcode = 1;
	r_strbuf_init (&op->esil);
	switch (data[0])
	{
		case 0x00:
		case 0x40:
		case 0x49:
		case 0x52:
		case 0x5b:
		case 0x64:
		case 0x6d:
		case 0x7f:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_NOP;
			break;
		case 0x01:
		case 0x11:
		case 0x21:
		case 0x31:
			gb_anal_mov_imm (anal->reg, op, data);
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0xf8:
			gb_anal_mov_hl_sp (anal->reg, op, data[1]);
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_MOV;
			op->type2 = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x06:
		case 0x0e:
		case 0x16:
		case 0x1e:
		case 0x26:
		case 0x2e:
		case 0x3e:
			gb_anal_mov_imm (anal->reg, op, data);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0xf9:
			gb_anal_mov_sp_hl (anal->reg, op);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_MOV;		// LD
			break;
		case 0x03:
		case 0x13:
		case 0x23:
		case 0x33:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_ADD;
			gb_anal_id (anal, op, data[0]);
			break;
		case 0x04:
		case 0x0c:
		case 0x14:
		case 0x1c:
		case 0x24:
		case 0x2c:
		case 0x3c:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ADD;		// INC
			gb_anal_id (anal, op, data[0]);
			break;
		case 0x34:
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_ADD;
			gb_anal_id (anal, op, data[0]);
			break;
		case 0xea:
			meta_gb_bankswitch_cmt (anal, addr, GB_SOFTCAST (data[1], data[2]));
			gb_anal_store (anal->reg, op, data);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x08:
			meta_gb_bankswitch_cmt (anal, addr, GB_SOFTCAST (data[1], data[2]));
			gb_anal_store (anal->reg, op, data);
			op->cycles = 20;
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x02:
		case 0x12:
		case 0xe2:
			gb_anal_store (anal->reg, op, data);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x36:
		case 0x22:
		case 0x32:
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x73:
		case 0x74:
		case 0x75:
		case 0x77:
			gb_anal_store_hl (anal->reg, op, data);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_STORE;	//LD
			break;
		case 0xe0:
			meta_gb_hardware_cmt (anal, data[1], addr);
			gb_anal_store (anal->reg, op, data);
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x47:
		case 0x48:
		case 0x4a:
		case 0x4b:
		case 0x4c:
		case 0x4d:
		case 0x4f:
		case 0x50:
		case 0x51:
		case 0x53:
		case 0x54:
		case 0x55:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5a:
		case 0x5c:
		case 0x5d:
		case 0x5f:
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:
		case 0x65:
		case 0x67:
		case 0x68:
		case 0x69:
		case 0x6a:
		case 0x6b:
		case 0x6c:
		case 0x6f:
		case 0x78:
		case 0x79:
		case 0x7a:
		case 0x7b:
		case 0x7c:
		case 0x7d:
			gb_anal_mov_reg (anal->reg, op, data[0]);
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_MOV;		// LD
			break;
		case 0x0a:
		case 0x1a:
		case 0xf2:
			gb_anal_load (anal->reg, op, data);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x2a:
		case 0x3a:
		case 0x46:
		case 0x4e:
		case 0x56:
		case 0x5e:
		case 0x66:
		case 0x6e:
		case 0x7e:
			gb_anal_load_hl (anal->reg, op, data[0]);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0xf0:
			gb_anal_load (anal->reg, op, data);
			meta_gb_hardware_cmt (anal, data[1], addr);
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0xfa:
			gb_anal_load (anal->reg, op, data);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x80:
		case 0x81:
		case 0x82:
		case 0x83:
		case 0x84:
		case 0x85:
		case 0x87:
		case 0x88:
		case 0x89:
		case 0x8a:
		case 0x8b:
		case 0x8c:
		case 0x8d:
		case 0x8f:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ADD;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
			gb_anal_add_hl (anal->reg, op, data[0]);
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x86:
		case 0x8e:
			op->type = R_ANAL_OP_TYPE_ADD;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0xc6:
		case 0xce:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_ADD;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xe8:
			gb_anal_add_sp (anal->reg, op, data[1]);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x90:
		case 0x91:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		case 0x97:
		case 0x98:
		case 0x99:
		case 0x9a:
		case 0x9b:
		case 0x9c:
		case 0x9d:
		case 0x9f:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_SUB;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0x96:
		case 0x9e:
			op->type = R_ANAL_OP_TYPE_SUB;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0xd6:
		case 0xde:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_SUB;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xa0:
		case 0xa1:
		case 0xa2:
		case 0xa3:
		case 0xa4:
		case 0xa5:
		case 0xa7:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_AND;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0xe6:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_AND;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xa6:
			op->type = R_ANAL_OP_TYPE_AND;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0x07:					//rlca
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ROL;
			gb_anal_cb_rlc (anal->reg, op, 7);
			break;
		case 0x17:					//rla
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ROL;
			gb_anal_cb_rl (anal->reg, op, 7);
			break;
		case 0x0f:					//rrca
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ROR;
			gb_anal_cb_rrc (anal->reg, op, 7);
			break;
		case 0x1f:					//rra
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_ROR;
			gb_anal_cb_rr (anal->reg, op, 7);
			break;
		case 0x2f:
			gb_anal_xor_cpl (anal->reg, op);	//cpl
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_XOR;
			break;
		case 0x3f:					//ccf
			gb_anal_xor_ccf (anal->reg, op);
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_XOR;
			break;
		case 0xa8:
		case 0xa9:
		case 0xaa:
		case 0xab:
		case 0xac:
		case 0xad:
		case 0xaf:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_XOR;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0xee:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_XOR;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xae:
			op->type = R_ANAL_OP_TYPE_XOR;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0xb0:
		case 0xb1:
		case 0xb2:
		case 0xb3:
		case 0xb4:
		case 0xb5:
		case 0xb7:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_OR;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0xf6:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_OR;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xb6:
			op->type = R_ANAL_OP_TYPE_OR;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0xb8:
		case 0xb9:
		case 0xba:
		case 0xbb:
		case 0xbc:
		case 0xbd:
		case 0xbf:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_CMP;
			gb_anal_xoaasc (anal->reg, op, data);
			break;
		case 0xfe:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_CMP;
			gb_anal_xoaasc_imm (anal->reg, op, data);
			break;
		case 0xbe:
			op->type = R_ANAL_OP_TYPE_CMP;
			gb_anal_xoaasc (anal->reg, op, data);
			op->cycles = 8;
			break;
		case 0xc0:
		case 0xc8:
		case 0xd0:
		case 0xd8:
			gb_anal_cond (anal->reg, op, data[0]);
			gb_anal_esil_cret (op, data[0]);
			op->eob = true;
			op->cycles = 20;
			op->failcycles = 8;
			op->type = R_ANAL_OP_TYPE_CRET;
			break;
		case 0xd9:
			gb_anal_mov_ime (anal->reg, op, data[0]);
			op->type2 = R_ANAL_OP_TYPE_MOV;
		case 0xc9:
			op->eob = true;
			op->cycles = 16;
			gb_anal_esil_ret (op);
			op->stackop = R_ANAL_STACK_INC;
			op->stackptr = -2;
			op->type = R_ANAL_OP_TYPE_RET;
			break;
		case 0x0b:
		case 0x1b:
		case 0x2b:
		case 0x3b:
			op->cycles = 8;
			op->type = R_ANAL_OP_TYPE_SUB;
			gb_anal_id (anal, op, data[0]);
			break;
		case 0x05:
		case 0x0d:
		case 0x15:
		case 0x1d:
		case 0x25:
		case 0x2d:
		case 0x3d:
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_SUB;		// DEC
			gb_anal_id (anal, op, data[0]);
			break;
		case 0x35:
			op->cycles = 12;
			op->type = R_ANAL_OP_TYPE_SUB;
			gb_anal_id (anal, op, data[0]);
			break;
		case 0xc5:
		case 0xd5:
		case 0xe5:
		case 0xf5:
			gb_anal_pp (anal->reg, op, data[0]);
			op->cycles = 16;
			op->stackop = R_ANAL_STACK_INC;
			op->stackptr = 2;
			op->type = R_ANAL_OP_TYPE_PUSH;
			break;
		case 0xc1:
		case 0xd1:
		case 0xe1:
		case 0xf1:
			gb_anal_pp (anal->reg, op, data[0]);
			op->cycles = 12;
			op->stackop = R_ANAL_STACK_INC;
			op->stackptr = -2;
			op->type = R_ANAL_OP_TYPE_POP;
			break;
		case 0xc3:
			if( gb_op_calljump (anal, op, data, addr)) {
				op->type = R_ANAL_OP_TYPE_JMP;
				gb_anal_esil_jmp (op);
			} else {
				op->type = R_ANAL_OP_TYPE_UJMP;
			}
			op->eob = true;
			op->cycles = 16;
			op->fail = addr+ilen;
			break;
		case 0x18:					// JR
			op->jump = addr + ilen + (st8)data[1];
			op->fail = addr + ilen;
			gb_anal_esil_jmp (op);
			op->cycles = 12;
			op->eob = true;
			op->type = R_ANAL_OP_TYPE_JMP;
			break;
		case 0x20:
		case 0x28:
		case 0x30:
		case 0x38:					//JR cond
			gb_anal_cond (anal->reg, op, data[0]);
			op->jump = addr + ilen + (st8)data[1];
			op->fail = addr + ilen;
			gb_anal_esil_cjmp (op, data[0]);
			op->cycles = 12;
			op->failcycles = 8;
			op->eob = true;
			op->type = R_ANAL_OP_TYPE_CJMP;
			break;
		case 0xc2:
		case 0xca:
		case 0xd2:
		case 0xda:
			if( gb_op_calljump (anal, op, data, addr)) {
				op->type = R_ANAL_OP_TYPE_CJMP;
			} else {
				op->type = R_ANAL_OP_TYPE_UCJMP;
			}
			op->eob = true;
			gb_anal_cond (anal->reg, op, data[0]);
			gb_anal_esil_cjmp (op, data[0]);
			op->cycles = 16;
			op->failcycles = 12;
			op->fail = addr+ilen;
			break;
		case 0xe9:
			op->cycles = 4;
			op->eob = true;
			op->type = R_ANAL_OP_TYPE_UJMP;
			gb_anal_jmp_hl (anal->reg, op);
			break;
		case 0x76:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->eob = true;			//halt migth wait for interrupts
			op->fail = addr + ilen;
			if (len > 1) {
				op->jump = addr + gbOpLength (gb_op[data[1]].type) + ilen;
			}
			break;
		case 0xcd:
			if (gb_op_calljump (anal, op, data, addr)) {
				op->type = R_ANAL_OP_TYPE_CALL;
			} else {
				op->type = R_ANAL_OP_TYPE_UCALL;
			}
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 24;
			break;
		case 0xc4:
		case 0xcc:
		case 0xd4:
		case 0xdc:
			gb_anal_cond (anal->reg, op, data[0]);
			if (gb_op_calljump (anal, op, data, addr)) {
				op->type = R_ANAL_OP_TYPE_CCALL;
			} else {
				op->type = R_ANAL_OP_TYPE_UCCALL;
			}
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_ccall (op, data[0]);
			op->cycles = 24;
			op->failcycles = 12;
			break;
                case 0xc7:				//rst 0
			op->jump = 0x00;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xcf:				//rst 8
                        op->jump = 0x08;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
                        break;
		case 0xd7:				//rst 16
			op->jump = 0x10;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xdf:				//rst 24
			op->jump = 0x18;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xe7:				//rst 32
			op->jump = 0x20;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xef:				//rst 40
			op->jump = 0x28;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xf7:				//rst 48
			op->jump = 0x30;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xff:				//rst 56
			op->jump = 0x38;
			op->fail = addr + ilen;
			op->eob = true;
			gb_anal_esil_call (op);
			op->cycles = 16;
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0xf3:				//di
		case 0xfb:				//ei
			gb_anal_mov_ime (anal->reg, op, data[0]);
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x37:
			gb_anal_mov_scf (anal->reg, op);
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x27:				//daa
			op->cycles = 4;
			op->type = R_ANAL_OP_TYPE_XOR;
			r_strbuf_set (&op->esil, "daa");
			break;
		case 0x10:				//stop
			op->type = R_ANAL_OP_TYPE_NULL;
			r_strbuf_set (&op->esil, "TODO,stop");
			break;
		case 0xcb:
			op->nopcode = 2;
			switch (data[1]>>3)
			{
				case 0:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ROL;
					gb_anal_cb_rlc (anal->reg, op, data[1]);
					break;
				case 1:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ROR;
					gb_anal_cb_rrc (anal->reg, op, data[1]);
					break;
				case 2:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ROL;
					gb_anal_cb_rl (anal->reg, op, data[1]);
					break;
				case 3:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ROR;
					gb_anal_cb_rr (anal->reg, op, data[1]);
					break;
				case 4:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_SAL;
					gb_anal_cb_sla (anal->reg, op, data[1]);
					break;
				case 6:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ROL;
					gb_anal_cb_swap (anal->reg, op, data[1]);
					break;
				case 5:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_SAR;
					gb_anal_cb_sra (anal->reg, op, data[1]);
					break;
				case 7:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_SHR;
					gb_anal_cb_srl (anal->reg, op, data[1]);
					break;
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
					if ((data[1] & 7) == 6) {
						op->cycles = 12;
					} else {
						op->cycles = 8;
					}
					op->type = R_ANAL_OP_TYPE_ACMP;
					gb_anal_and_bit (anal->reg, op, data[1]);
					break;			//bit
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					gb_anal_and_res (anal, op, data[1]);
					op->type = R_ANAL_OP_TYPE_AND;
					break;			//res
				case 24:
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
					if ((data[1] & 7) == 6) {
						op->cycles = 16;
					} else {
						op->cycles = 8;
					}
					gb_anal_or_set (anal, op, data[1]);
					op->type = R_ANAL_OP_TYPE_OR;
					break;			//set
			}
	}
	if (op->type == R_ANAL_OP_TYPE_CALL)
	{
		op->stackop = R_ANAL_STACK_INC;
		op->stackptr = 2;
	}
	return op->size;
}