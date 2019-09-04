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
struct cr16_cmd {int /*<<< orphan*/  type; int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
 int /*<<< orphan*/  CR16_TYPE_MOV ; 
 char** instrs_4bit ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

int cr16_decode_loadm_storm(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 2;
	ut16 c;

	c = r_read_le16 (instr);

	if ((c & 0x1F) != 4) {
		return -1;
	}

	snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "%s",
			instrs_4bit[c >> 7]);
	snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "$0x%x",
			((c >> 5) & 0x3) + 1);

	cmd->type = CR16_TYPE_MOV;

	return ret;
}