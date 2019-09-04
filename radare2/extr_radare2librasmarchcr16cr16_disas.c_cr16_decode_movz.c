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
struct cr16_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
#define  CR16_MOVXB 129 
#define  CR16_MOVZB 128 
 size_t cr16_get_dstreg (int) ; 
 size_t cr16_get_srcreg (int) ; 
 char** cr16_regs_names ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

int cr16_decode_movz(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 2;
	ut16 c;
	c = r_read_le16 (instr);

	if (c & 1) {
		return -1;
	}

	switch (c >> 9) {
	case CR16_MOVXB:
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "movxb");
		break;
	case CR16_MOVZB:
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "movzb");
		break;
	default:
		return -1;
	}

	snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "%s,%s",
			cr16_regs_names[cr16_get_srcreg(c)],
			cr16_regs_names[cr16_get_dstreg(c)]);

	return ret;
}