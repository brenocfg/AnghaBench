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
#define  CR16_POP 131 
#define  CR16_POPRET_1 130 
#define  CR16_POPRET_2 129 
#define  CR16_PUSH 128 
 char** cr16_regs_names ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int cr16_decode_push_pop(const ut8 *instr, struct cr16_cmd *cmd)
{
	int ret = 2;
	ut16 c;

	c = r_read_le16 (instr);

	if ((c & 1)) {
		return -1;
	}

	switch (c >> 7) {
	case CR16_PUSH:
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "push");
		break;
	case CR16_POP:
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "pop");
		break;
	case CR16_POPRET_1:
	case CR16_POPRET_2:
		snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "popret");
		break;
	}

	snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "$0x%x,%s",
			((c >> 5) & 0x3) + 1,
			cr16_regs_names[(c >> 1) & 0xF]);

	return ret;
}