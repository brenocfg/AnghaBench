#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_9__ {char* mnemonic; int noperands; TYPE_1__* operands; } ;
typedef  TYPE_2__ rsp_instruction ;
struct TYPE_11__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  big_endian; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  buf_asm; } ;
struct TYPE_8__ {int type; size_t u; size_t s; } ;
typedef  TYPE_3__ RAsmOp ;
typedef  TYPE_4__ RAsm ;

/* Variables and functions */
#define  RSP_OPND_BASE_OFFSET 141 
#define  RSP_OPND_C0_REG 140 
#define  RSP_OPND_C2_ACCU 139 
#define  RSP_OPND_C2_CREG 138 
#define  RSP_OPND_C2_VREG 137 
#define  RSP_OPND_C2_VREG_BYTE 136 
#define  RSP_OPND_C2_VREG_ELEMENT 135 
#define  RSP_OPND_C2_VREG_SCALAR 134 
#define  RSP_OPND_GP_REG 133 
#define  RSP_OPND_OFFSET 132 
#define  RSP_OPND_SHIFT_AMOUNT 131 
#define  RSP_OPND_SIMM 130 
#define  RSP_OPND_TARGET 129 
#define  RSP_OPND_ZIMM 128 
 int /*<<< orphan*/  r_read_ble32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rsp_c0_reg_soft_names ; 
 int /*<<< orphan*/ * rsp_c2_accu_names ; 
 int /*<<< orphan*/ * rsp_c2_creg_names ; 
 int /*<<< orphan*/ * rsp_c2_vreg_element_names ; 
 int /*<<< orphan*/ * rsp_c2_vreg_names ; 
 int /*<<< orphan*/ * rsp_gp_reg_soft_names ; 
 TYPE_2__ rsp_instruction_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snappendf (char**,size_t*,char*,...) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	rsp_instruction r_instr;
	int i;
	char* buffer;
	size_t size;

	/* all instructions are 32bit words */
	if (len < 4) {
		op->size = 0;
		return 0;
	}
	op->size = 4;

	ut32 iw = r_read_ble32 (buf, a->big_endian);
	r_instr = rsp_instruction_decode (a->pc, iw);

	buffer = r_strbuf_get (&op->buf_asm);
	size = sizeof (op->buf_asm);

	snappendf (&buffer, &size, r_instr.mnemonic);
	for (i = 0; i < r_instr.noperands; ++i) {
		snappendf (&buffer, &size, "%s", (i == 0) ? " " : ", ");

		switch (r_instr.operands[i].type) {
		case RSP_OPND_GP_REG:
			snappendf (&buffer, &size, "%s", rsp_gp_reg_soft_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_OFFSET:
		case RSP_OPND_TARGET:
			snappendf (&buffer, &size, "0x%08x", r_instr.operands[i].u);
			break;
		case RSP_OPND_ZIMM:
			snappendf (&buffer, &size, "0x%04x", r_instr.operands[i].u >> ((r_instr.operands[i].u & ~0xffff) ? 16 : 0));
			break;
		case RSP_OPND_SIMM:
			snappendf (&buffer, &size, "%s0x%04x",
			(r_instr.operands[i].s<0)?"-":"",
			(r_instr.operands[i].s<0)?-r_instr.operands[i].s:r_instr.operands[i].s);
			break;
		case RSP_OPND_SHIFT_AMOUNT:
			snappendf (&buffer, &size, "%u", r_instr.operands[i].u);
			break;
		case RSP_OPND_BASE_OFFSET:
			snappendf (&buffer, &size, "%s0x%04x(%s)",
			(r_instr.operands[i].s<0)?"-":"",
			(r_instr.operands[i].s<0)?-r_instr.operands[i].s:r_instr.operands[i].s,
			rsp_gp_reg_soft_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_C0_REG:
			snappendf (&buffer, &size, "%s", rsp_c0_reg_soft_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_C2_CREG:
			snappendf (&buffer, &size, "%s", rsp_c2_creg_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_C2_ACCU:
			snappendf (&buffer, &size, "%s", rsp_c2_accu_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_C2_VREG:
			snappendf (&buffer, &size, "%s", rsp_c2_vreg_names[r_instr.operands[i].u]);
			break;
		case RSP_OPND_C2_VREG_BYTE:
		case RSP_OPND_C2_VREG_SCALAR:
			snappendf (&buffer, &size, "%s[%u]", rsp_c2_vreg_names[r_instr.operands[i].u], r_instr.operands[i].s);
			break;
		case RSP_OPND_C2_VREG_ELEMENT:
			snappendf (&buffer, &size, "%s%s", rsp_c2_vreg_names[r_instr.operands[i].u], rsp_c2_vreg_element_names[r_instr.operands[i].s]);
			break;
		default: /* should not happend */
			snappendf (&buffer, &size, "???");
			break;
		}
	}

	return op->size;
}