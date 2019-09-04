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
typedef  int ut32 ;
typedef  int ut16 ;
struct cr16_cmd {int reladdr; int /*<<< orphan*/  operands; int /*<<< orphan*/  type; int /*<<< orphan*/  instr; } ;
typedef  void* st32 ;
typedef  void* st16 ;

/* Variables and functions */
 int CR16_BCOND_2 ; 
 scalar_t__ CR16_INSTR_MAXLEN ; 
 int /*<<< orphan*/  CR16_TYPE_BCOND ; 
 int /*<<< orphan*/  CR16_TYPE_JUMP ; 
 int GET_BIT (int,int) ; 
 char** cr16_conds ; 
 size_t cr16_get_cond (int) ; 
 scalar_t__ cr16_get_opcode_i (int) ; 
 int cr16_get_opcode_low (int) ; 
 int r_read_at_le16 (int /*<<< orphan*/  const*,int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int cr16_decode_bcond_br(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 2;

	ut16 c, disp;
	ut32 disp32;

	c = r_read_le16 (instr);

	if (c & 0x1) {
		return -1;
	}

	if (!(c >> 14) && cr16_get_opcode_low (c) != 0xA) {
		return -1;
	}

	if (((c >> 5) & 0xF) == 0xE) {
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "br");
		if (((c >> 1) & 0x7) == 0x7) {
			disp = r_read_at_le16 (instr, 2);

			disp32 = disp | (((c >> 4) & 0x1) << 16);
			ret = 4;
			snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
					"0x%08x", disp32);

			if (disp32 & 0x10000) {
				disp32 |= 0xFFFE0000;
				cmd->reladdr = (st32)disp32;
			} else {
				cmd->reladdr = disp32;
			}
		} else {
			if (cr16_get_opcode_i(c)) {
				ret = 4;
				disp = r_read_at_le16 (instr, 2);
				disp32 = disp | (((c >> 1) & 0x7) << 17) | (((c >> 4) & 1) << 16);
				if (disp32 & 0x80000) {
					disp32 |= 0xFFF00000;
					cmd->reladdr = (st32)disp32;
				} else {
					cmd->reladdr = disp32;
				}
				snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "0x%08x", disp32);
			} else {
				disp = (c & 0x1F) | ((c >> 4) & 0x1E0);

				if (disp & 0x0100) {
					disp |= 0xFE00;
					cmd->reladdr = (st16)disp;
				} else {
					cmd->reladdr = disp;
				}

				snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "0x%04x", disp);
			}
		}
		cmd->type = CR16_TYPE_JUMP;
	} else {
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "b%s",
				cr16_conds[cr16_get_cond(c)]);
		if (c & 0x1) {
			return -1;
		}

		if ((c >> 8) == CR16_BCOND_2) {
			disp = r_read_at_le16 (instr, 2);
			disp32 = disp | (GET_BIT(c, 4) << 16);
			if (disp32 & 0x80000) {
				disp32 |= 0xFFF00000;
				cmd->reladdr = (st32)disp32;
			} else {
				cmd->reladdr = disp32;
			}
			ret = 4;
		} else {
			disp = (c & 0x1F) | ((c >> 4) & 0x1E0);

			if (disp & 0x0100) {
				disp |= 0xFE00;
				cmd->reladdr = (st16)disp;
			} else {
				cmd->reladdr = disp;
			}

			disp32 = disp;
		}

		cmd->type = CR16_TYPE_BCOND;
		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "0x%04x", disp32);
	}

	return ret;
}