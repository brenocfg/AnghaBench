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
typedef  int ut16 ;
struct TYPE_6__ {int args; char* mnemonic; } ;
struct TYPE_5__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  scalar_t__ PicBaselineOpcode ;
typedef  TYPE_2__ PicBaselineOpInfo ;

/* Variables and functions */
 scalar_t__ PIC_BASELINE_OPCODE_INVALID ; 
#define  PIC_BASELINE_OP_ARGS_1D_5F 136 
 int PIC_BASELINE_OP_ARGS_1D_5F_MASK_D ; 
 int PIC_BASELINE_OP_ARGS_1D_5F_MASK_F ; 
#define  PIC_BASELINE_OP_ARGS_2F 135 
 int PIC_BASELINE_OP_ARGS_2F_MASK_F ; 
#define  PIC_BASELINE_OP_ARGS_3B_5F 134 
 int PIC_BASELINE_OP_ARGS_3B_5F_MASK_B ; 
 int PIC_BASELINE_OP_ARGS_3B_5F_MASK_F ; 
#define  PIC_BASELINE_OP_ARGS_3F 133 
 int PIC_BASELINE_OP_ARGS_3F_MASK_F ; 
#define  PIC_BASELINE_OP_ARGS_3K 132 
 int PIC_BASELINE_OP_ARGS_3K_MASK_K ; 
#define  PIC_BASELINE_OP_ARGS_5F 131 
 int PIC_BASELINE_OP_ARGS_5F_MASK_F ; 
#define  PIC_BASELINE_OP_ARGS_8K 130 
 int PIC_BASELINE_OP_ARGS_8K_MASK_K ; 
#define  PIC_BASELINE_OP_ARGS_9K 129 
 int PIC_BASELINE_OP_ARGS_9K_MASK_K ; 
#define  PIC_BASELINE_OP_ARGS_NONE 128 
 TYPE_2__* pic_baseline_get_op_info (scalar_t__) ; 
 scalar_t__ pic_baseline_get_opcode (int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 char* sdb_fmt (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int pic_baseline_disassemble(RAsmOp *op, char *opbuf, const ut8 *b, int l) {
#define EMIT_INVALID { \
	op->size = 1; \
	strcpy (opbuf, "invalid"); \
	return 1; \
}
	if (!b || l < 2) {
		EMIT_INVALID
	}

	ut16 instr = r_read_le16 (b);
	PicBaselineOpcode opcode = pic_baseline_get_opcode (instr);
	if (opcode == PIC_BASELINE_OPCODE_INVALID) {
		EMIT_INVALID
	}

	const PicBaselineOpInfo *op_info = pic_baseline_get_op_info(opcode);
	if (!op_info) {
		EMIT_INVALID
	}

#undef EMIT_INVALID

	op->size = 2;

	const char *buf_asm = "invalid";
	switch (op_info->args) {
	case PIC_BASELINE_OP_ARGS_NONE:
		buf_asm = op_info->mnemonic;
		break;
	case PIC_BASELINE_OP_ARGS_2F:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_2F_MASK_F);
		break;
	case PIC_BASELINE_OP_ARGS_3F:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_3F_MASK_F);
		break;
	case PIC_BASELINE_OP_ARGS_3K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_3K_MASK_K);
		break;
	case PIC_BASELINE_OP_ARGS_1D_5F:
		buf_asm = sdb_fmt ("%s 0x%x, %c", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_1D_5F_MASK_F,
				  (instr & PIC_BASELINE_OP_ARGS_1D_5F_MASK_D) >> 5 ? 'f' : 'w');
		break;
	case PIC_BASELINE_OP_ARGS_5F:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_5F_MASK_F);
		break;
	case PIC_BASELINE_OP_ARGS_3B_5F:
		buf_asm = sdb_fmt ("%s 0x%x, 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_3B_5F_MASK_F,
				  (instr & PIC_BASELINE_OP_ARGS_3B_5F_MASK_B) >> 5);
		break;
	case PIC_BASELINE_OP_ARGS_8K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_8K_MASK_K);
		break;
	case PIC_BASELINE_OP_ARGS_9K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_BASELINE_OP_ARGS_9K_MASK_K);
		break;
	}
	strcpy (opbuf, buf_asm);

	return op->size;
}