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
typedef  int st16 ;
typedef  int /*<<< orphan*/  fsr_op ;
struct TYPE_6__ {int args; char* mnemonic; } ;
struct TYPE_5__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  scalar_t__ PicMidrangeOpcode ;
typedef  TYPE_2__ PicMidrangeOpInfo ;

/* Variables and functions */
 scalar_t__ PIC_MIDRANGE_OPCODE_ADDFSR ; 
 scalar_t__ PIC_MIDRANGE_OPCODE_INVALID ; 
#define  PIC_MIDRANGE_OP_ARGS_11K 138 
 int PIC_MIDRANGE_OP_ARGS_11K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_1D_7F 137 
 int PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_D ; 
 int PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_1N_2M 136 
 int PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_M ; 
 int PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_N ; 
#define  PIC_MIDRANGE_OP_ARGS_1N_6K 135 
 int PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_K ; 
 int PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_N ; 
#define  PIC_MIDRANGE_OP_ARGS_2F 134 
 int PIC_MIDRANGE_OP_ARGS_2F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_3B_7F 133 
 int PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_B ; 
 int PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_4K 132 
 int PIC_MIDRANGE_OP_ARGS_4K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_7F 131 
 int PIC_MIDRANGE_OP_ARGS_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_8K 130 
 int PIC_MIDRANGE_OP_ARGS_8K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_9K 129 
 int PIC_MIDRANGE_OP_ARGS_9K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_NONE 128 
 char** PicMidrangeFsrOps ; 
 TYPE_2__* pic_midrange_get_op_info (scalar_t__) ; 
 scalar_t__ pic_midrange_get_opcode (int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 char* sdb_fmt (char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int pic_midrange_disassemble (RAsmOp *op, char *opbuf, const ut8 *b, int l) {
	char fsr_op[6];
	st16 branch;

#define EMIT_INVALID {\
		op->size = 2; \
		strcpy (opbuf, "invalid"); \
		return 1; \
	}
	if (!b || l < 2) {
		EMIT_INVALID
	}

	ut16 instr = r_read_le16 (b);
	PicMidrangeOpcode opcode = pic_midrange_get_opcode (instr);
	if (opcode == PIC_MIDRANGE_OPCODE_INVALID) {
		EMIT_INVALID
	}

	const PicMidrangeOpInfo *op_info = pic_midrange_get_op_info (opcode);
	if (!op_info) {
		EMIT_INVALID
	}

#undef EMIT_INVALID

	op->size = 2;

	const char *buf_asm = NULL;
	switch (op_info->args) {
	case PIC_MIDRANGE_OP_ARGS_NONE:
		buf_asm = op_info->mnemonic;
		break;
	case PIC_MIDRANGE_OP_ARGS_2F:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_2F_MASK_F);
		break;
	case PIC_MIDRANGE_OP_ARGS_7F:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_7F_MASK_F);
		break;
	case PIC_MIDRANGE_OP_ARGS_1D_7F:
		buf_asm = sdb_fmt ("%s 0x%x, %c", op_info->mnemonic,
			  instr & PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_F,
			  (instr & PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_D) >> 7 ?  'f' : 'w');
		break;
	case PIC_MIDRANGE_OP_ARGS_1N_6K:
		if (opcode == PIC_MIDRANGE_OPCODE_ADDFSR) {
			buf_asm = sdb_fmt ( "%s FSR%d, 0x%x", op_info->mnemonic,
					(instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_N) >>
					6, instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_K);
		} else {
			buf_asm = sdb_fmt ("%s 0x%x[FSR%d]", op_info->mnemonic,
				instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_K,
				(instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_N) >> 6);
		}
		break;
	case PIC_MIDRANGE_OP_ARGS_3B_7F:
		buf_asm = sdb_fmt ("%s 0x%x, %d", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_F,
			  (instr & PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_B) >> 7);
		break;
	case PIC_MIDRANGE_OP_ARGS_4K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_4K_MASK_K);
		break;
	case PIC_MIDRANGE_OP_ARGS_8K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_8K_MASK_K);
		break;
	case PIC_MIDRANGE_OP_ARGS_9K:
		branch = (instr & PIC_MIDRANGE_OP_ARGS_9K_MASK_K);
		branch |= ((branch & 0x100) ? 0xfe00 : 0);
		buf_asm = sdb_fmt ("%s %s0x%x",
			  op_info->mnemonic, branch < 0 ? "-" : "",
			  branch < 0 ? -branch : branch);
		break;
	case PIC_MIDRANGE_OP_ARGS_11K:
		buf_asm = sdb_fmt ("%s 0x%x", op_info->mnemonic, instr & PIC_MIDRANGE_OP_ARGS_11K_MASK_K);
		break;
	case PIC_MIDRANGE_OP_ARGS_1N_2M:
		snprintf (
			fsr_op, sizeof (fsr_op),
			PicMidrangeFsrOps[instr &
					  PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_M],
			(instr & PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_N) >> 2);
		buf_asm = sdb_fmt ("%s %s", op_info->mnemonic, fsr_op);
		break;
	}
	if (buf_asm) {
		strcpy (opbuf, buf_asm);
	}
	return op->size;
}