#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut16 ;
struct cr16_cmd {void* type; int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR16_INSTR_MAXLEN ; 
#define  CR16_JAL 129 
#define  CR16_JUMP 128 
 void* CR16_TYPE_JUMP_UNK ; 
 char** cr16_conds ; 
 size_t cr16_get_dstreg (int) ; 
 size_t cr16_get_srcreg (int) ; 
 int /*<<< orphan*/  cr16_print_reg_reg (struct cr16_cmd*,size_t,size_t) ; 
 char** cr16_regs_names ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cr16_decode_jmp(const ut8 *instr, struct cr16_cmd *cmd)
{
	ut16 c;
	int ret = 2;

	c = r_read_le16 (instr);

	switch (c >> 9) {
	case CR16_JUMP:
		if (((c >> 5) & 0xf) == 0xE) {
			snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "jump");
		} else {
			snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "j%s",
				cr16_conds[cr16_get_dstreg(c)]);
		}
		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "%s",
			cr16_regs_names[cr16_get_srcreg(c)]);
		break;
	case CR16_JAL:
		if (!(c & 1)) {
			ret = -1;
			break;
		}
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "jal");
		cr16_print_reg_reg(cmd, cr16_get_dstreg(c), cr16_get_srcreg(c));
		cmd->type = CR16_TYPE_JUMP_UNK;
		break;
	case 0x0B:
		if (!(c & 1)) {
			strncpy(cmd->instr, "jal", CR16_INSTR_MAXLEN - 1);
			snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "(%s,%s),(%s,%s)",
					cr16_regs_names[cr16_get_dstreg(c) + 1],
					cr16_regs_names[cr16_get_dstreg(c)],
					cr16_regs_names[cr16_get_srcreg(c) + 1],
					cr16_regs_names[cr16_get_srcreg(c)]);
		} else if (cr16_get_dstreg(c) != 0xE) {
			snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "j%s",
					cr16_conds[cr16_get_dstreg(c)]);
			snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "(%s,%s)",
					cr16_regs_names[cr16_get_srcreg(c) + 1],
					cr16_regs_names[cr16_get_srcreg(c)]);
		} else {
			strncpy(cmd->instr, "jump", CR16_INSTR_MAXLEN - 1);
			snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "(%s,%s)",
					cr16_regs_names[cr16_get_srcreg(c) + 1],
					cr16_regs_names[cr16_get_srcreg(c)]);
		}
		break;
	default:
		return -1;
	}

	cmd->type = CR16_TYPE_JUMP_UNK;
	return ret;
}