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
struct cr16_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
#define  CR16_BAL 129 
 scalar_t__ CR16_INSTR_MAXLEN ; 
#define  CR16_TBIT_R_R 128 
 size_t cr16_get_dstreg (int) ; 
 char** cr16_regs_names ; 
 int r_read_at_le16 (int /*<<< orphan*/  const*,int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int cr16_decode_bal(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 4;
	ut16 c, disp16;
	ut32 disp32;

	c = r_read_le16 (instr);
	disp16 = r_read_at_le16 (instr, 2);

	snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "bal");

	switch (c >> 9) {
	case CR16_BAL:
		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "%s,0x%x",
			cr16_regs_names[cr16_get_dstreg(c)], disp16);
		break;
	case CR16_TBIT_R_R:
		disp32 = disp16 | (((c >> 1) & 0xF) << 16);
		snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "(%s,%s),0x%08x",
			cr16_regs_names[cr16_get_dstreg(c) + 1],
			cr16_regs_names[cr16_get_dstreg(c)], disp32);
		break;
	default:
		return -1;
	}

	return ret;
}