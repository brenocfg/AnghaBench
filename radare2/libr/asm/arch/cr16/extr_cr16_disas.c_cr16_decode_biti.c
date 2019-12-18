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
typedef  int ut8 ;
typedef  int ut32 ;
typedef  int ut16 ;
struct cr16_cmd {int /*<<< orphan*/  type; int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
 int /*<<< orphan*/  CR16_TYPE_BIT ; 
 int cr16_get_dstreg (int) ; 
 scalar_t__ cr16_get_opcode_i (int) ; 
 int cr16_get_srcreg (int) ; 
 char** cr16_regs_names ; 
 char** ops_biti ; 
 int r_read_at_le16 (int const*,int) ; 
 int r_read_le16 (int const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

int cr16_decode_biti(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 2;
	ut32 abs18;
	ut16 c, disp16;
	ut8 reg, position;

	c = r_read_le16 (instr);

	if (((c >> 6) & 0x3) == 0x3) {
		return -1;
	}

	reg = cr16_get_dstreg(c);
	position = cr16_get_srcreg(c);

	if (!(reg & 0x6)) {
		return -1;
	}

	snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "%s%c",
			ops_biti[(c >> 6) & 0x3],
			cr16_get_opcode_i(c) ? 'w' : 'b');

	switch (((c >> 13) & 0x2) | (c & 0x1)) {
	case 0x0:
		ret = 4;
		disp16 = r_read_at_le16 (instr, 2);

		abs18 = disp16 | ((reg & 0x1) << 16) | ((reg >> 3) << 17);

		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
				"$0x%02x,0x%08x", position, abs18);

		break;
	case 0x1:
		ret = 4;

		disp16 = r_read_at_le16 (instr, 2);

		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
				"$0x%02x,0x%04x(%s)", position,
				disp16, cr16_regs_names[reg & 0x9]);

		break;
	case 0x3:
		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
				"$0x%02x,0(%s)", position,
				cr16_regs_names[reg & 0x9]);
		break;
	default:
		ret = -1;
	}

	cmd->type = CR16_TYPE_BIT;
	return ret;
}