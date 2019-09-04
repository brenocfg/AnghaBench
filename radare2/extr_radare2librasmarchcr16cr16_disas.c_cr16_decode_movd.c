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
 scalar_t__ CR16_INSTR_MAXLEN ; 
 char** cr16_regs_names ; 
 int r_read_at_le16 (int /*<<< orphan*/  const*,int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

int cr16_decode_movd(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 4;
	ut16 c;
	ut16 imm;
	ut32 imm32;

	c = r_read_le16 (instr);
	imm = r_read_at_le16 (instr, 2);

	if (c & 1) {
		return -1;
	}

	snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "movd");

	imm32 = imm | (((c >> 4) & 1) << 16) | (((c >> 9) & 1) << 20) | (((c >> 1) & 0x7) << 17);
	snprintf (cmd->operands, CR16_INSTR_MAXLEN - 1, "$0x%08x,(%s,%s)", imm32,
			cr16_regs_names[((c >> 5) & 0xF) + 1],
			cr16_regs_names[(c >> 5) & 0xF]);

	return ret;
}