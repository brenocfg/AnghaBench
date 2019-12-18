#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int st32 ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_11__ {TYPE_1__* detail; } ;
typedef  TYPE_4__ cs_insn ;
struct TYPE_10__ {int type; int value; } ;
struct TYPE_9__ {int base; int index; int scale; int disp; } ;
struct TYPE_12__ {int type; int reg; int fp; int vector_index; scalar_t__ subtracted; TYPE_3__ shift; int /*<<< orphan*/  setend; int /*<<< orphan*/  imm; TYPE_2__ mem; } ;
typedef  TYPE_5__ cs_arm_op ;
struct TYPE_13__ {int op_count; int vector_size; scalar_t__ vector_data; int cps_mode; int cps_flag; scalar_t__ cc; int mem_barrier; scalar_t__ writeback; scalar_t__ update_flags; scalar_t__ usermode; TYPE_5__* operands; } ;
typedef  TYPE_6__ cs_arm ;
struct TYPE_8__ {TYPE_6__ arm; } ;
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 scalar_t__ ARM_CC_AL ; 
 scalar_t__ ARM_CC_INVALID ; 
 int ARM_CPSFLAG_INVALID ; 
 int ARM_CPSMODE_INVALID ; 
 int ARM_MB_INVALID ; 
#define  ARM_OP_CIMM 147 
#define  ARM_OP_FP 146 
#define  ARM_OP_IMM 145 
#define  ARM_OP_MEM 144 
#define  ARM_OP_PIMM 143 
#define  ARM_OP_REG 142 
#define  ARM_OP_SETEND 141 
#define  ARM_OP_SYSREG 140 
 int ARM_REG_INVALID ; 
#define  ARM_SETEND_BE 139 
#define  ARM_SETEND_LE 138 
#define  ARM_SFT_ASR 137 
#define  ARM_SFT_ASR_REG 136 
 int ARM_SFT_INVALID ; 
#define  ARM_SFT_LSL 135 
#define  ARM_SFT_LSL_REG 134 
#define  ARM_SFT_LSR 133 
#define  ARM_SFT_LSR_REG 132 
#define  ARM_SFT_ROR 131 
#define  ARM_SFT_ROR_REG 130 
#define  ARM_SFT_RRX 129 
#define  ARM_SFT_RRX_REG 128 
 scalar_t__ ARM_VECTORDATA_INVALID ; 
 int cc_name (scalar_t__) ; 
 int cs_reg_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int shift_type_name (int) ; 
 int vector_data_type_name (scalar_t__) ; 

__attribute__((used)) static void opex(RStrBuf *buf, csh handle, cs_insn *insn) {
	int i;
	r_strbuf_init (buf);
	r_strbuf_append (buf, "{");
	cs_arm *x = &insn->detail->arm;
	r_strbuf_append (buf, "\"operands\":[");
	for (i = 0; i < x->op_count; i++) {
		cs_arm_op *op = &x->operands[i];
		if (i > 0) {
			r_strbuf_append (buf, ",");
		}
		r_strbuf_append (buf, "{");
		switch (op->type) {
		case ARM_OP_REG:
			r_strbuf_append (buf, "\"type\":\"reg\"");
			r_strbuf_appendf (buf, ",\"value\":\"%s\"", cs_reg_name (handle, op->reg));
			break;
		case ARM_OP_IMM:
			r_strbuf_append (buf, "\"type\":\"imm\"");
			r_strbuf_appendf (buf, ",\"value\":%d", (st32)op->imm);
			break;
		case ARM_OP_MEM:
			r_strbuf_append (buf, "\"type\":\"mem\"");
			if (op->mem.base != ARM_REG_INVALID) {
				r_strbuf_appendf (buf, ",\"base\":\"%s\"", cs_reg_name (handle, op->mem.base));
			}
			if (op->mem.index != ARM_REG_INVALID) {
				r_strbuf_appendf (buf, ",\"index\":\"%s\"", cs_reg_name (handle, op->mem.index));
			}
			r_strbuf_appendf (buf, ",\"scale\":%d", op->mem.scale);
			r_strbuf_appendf (buf, ",\"disp\":%d", op->mem.disp);
			break;
		case ARM_OP_FP:
			r_strbuf_append (buf, "\"type\":\"fp\"");
			r_strbuf_appendf (buf, ",\"value\":%lf", op->fp);
			break;
		case ARM_OP_CIMM:
			r_strbuf_append (buf, "\"type\":\"cimm\"");
			r_strbuf_appendf (buf, ",\"value\":%d", (st32)op->imm);
			break;
		case ARM_OP_PIMM:
			r_strbuf_append (buf, "\"type\":\"pimm\"");
			r_strbuf_appendf (buf, ",\"value\":%d", (st32)op->imm);
			break;
		case ARM_OP_SETEND:
			r_strbuf_append (buf, "\"type\":\"setend\"");
			switch (op->setend) {
			case ARM_SETEND_BE:
				r_strbuf_append (buf, ",\"value\":\"be\"");
				break;
			case ARM_SETEND_LE:
				r_strbuf_append (buf, ",\"value\":\"le\"");
				break;
			default:
				r_strbuf_append (buf, ",\"value\":\"invalid\"");
				break;
			}
			break;
		case ARM_OP_SYSREG:
			r_strbuf_append (buf, "\"type\":\"sysreg\"");
			r_strbuf_appendf (buf, ",\"value\":\"%s\"", cs_reg_name (handle, op->reg));
			break;
		default:
			r_strbuf_append (buf, ",\"type\":\"invalid\"");
			break;
		}
		if (op->shift.type != ARM_SFT_INVALID) {
			r_strbuf_append (buf, ",\"shift\":{");
			switch (op->shift.type) {
			case ARM_SFT_ASR:
			case ARM_SFT_LSL:
			case ARM_SFT_LSR:
			case ARM_SFT_ROR:
			case ARM_SFT_RRX:
				r_strbuf_appendf (buf, "\"type\":\"%s\"", shift_type_name (op->shift.type));
				r_strbuf_appendf (buf, ",\"value\":\"%u\"", op->shift.value);
				break;
			case ARM_SFT_ASR_REG:
			case ARM_SFT_LSL_REG:
			case ARM_SFT_LSR_REG:
			case ARM_SFT_ROR_REG:
			case ARM_SFT_RRX_REG:
				r_strbuf_appendf (buf, "\"type\":\"%s\"", shift_type_name (op->shift.type));
				r_strbuf_appendf (buf, ",\"value\":\"%d\"", cs_reg_name (handle, op->shift.value));
				break;
			default:
				break;
			}
			r_strbuf_append (buf, "}");
		}
		if (op->vector_index != -1) {
			r_strbuf_appendf (buf, ",\"vector_index\":\"%d\"", op->vector_index);
		}
		if (op->subtracted) {
			r_strbuf_append (buf, ",\"subtracted\":true");
		}
		r_strbuf_append (buf, "}");
	}
	r_strbuf_append (buf, "]");
	if (x->usermode) {
		r_strbuf_append (buf, ",\"usermode\":true");
	}
	if (x->update_flags) {
		r_strbuf_append (buf, ",\"update_flags\":true");
	}
	if (x->writeback) {
		r_strbuf_append (buf, ",\"writeback\":true");
	}
	if (x->vector_size) {
		r_strbuf_appendf (buf, ",\"vector_size\":%d", x->vector_size);
	}
	if (x->vector_data != ARM_VECTORDATA_INVALID) {
		r_strbuf_appendf (buf, ",\"vector_data\":\"%s\"", vector_data_type_name (x->vector_data));
	}
	if (x->cps_mode != ARM_CPSMODE_INVALID) {
		r_strbuf_appendf (buf, ",\"cps_mode\":%d", x->cps_mode);
	}
	if (x->cps_flag != ARM_CPSFLAG_INVALID) {
		r_strbuf_appendf (buf, ",\"cps_flag\":%d", x->cps_flag);
	}
	if (x->cc != ARM_CC_INVALID && x->cc != ARM_CC_AL) {
		r_strbuf_appendf (buf, ",\"cc\":\"%s\"", cc_name (x->cc));
	}
	if (x->mem_barrier != ARM_MB_INVALID) {
		r_strbuf_appendf (buf, ",\"mem_barrier\":%d", x->mem_barrier - 1);
	}
	r_strbuf_append (buf, "}");
}