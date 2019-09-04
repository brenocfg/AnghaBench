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
struct v850_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  V850_INSTR_MAXLEN ; 
#define  V850_LDB 131 
#define  V850_LDHW 130 
#define  V850_STB 129 
#define  V850_STHW 128 
 size_t get_opcode (int) ; 
 int get_reg1 (int) ; 
 int get_reg2 (int) ; 
 char** instrs ; 
 int r_read_at_le16 (int /*<<< orphan*/  const*,int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int decode_load_store(const ut8 *instr, int len, struct v850_cmd *cmd) {
	if (len < 4) {
		return -1;
	}

	ut16 word1 = r_read_le16 (instr);
	ut16 word2 = r_read_at_le16 (instr, 2);

	switch (get_opcode (word1)) {
	case V850_STB:
		snprintf (cmd->instr, V850_INSTR_MAXLEN - 1, "%s.b", instrs[get_opcode (word1)]);
		snprintf (cmd->operands, V850_INSTR_MAXLEN - 1, "r%d, 0x%x[r%d]",
			       get_reg2 (word1), word2, get_reg1 (word1));
		break;
	case V850_LDB:
		snprintf (cmd->instr, V850_INSTR_MAXLEN - 1, "%s.b", instrs[get_opcode (word1)]);
		snprintf (cmd->operands, V850_INSTR_MAXLEN - 1, "0x%x[r%d], r%d",
			       get_reg1 (word1), word2, get_reg2 (word1));
		break;
	case V850_LDHW:
		snprintf (cmd->instr, V850_INSTR_MAXLEN - 1, "%s.%c",
				instrs[get_opcode (word1)], word2 & 1 ? 'w' : 'h');
		snprintf (cmd->operands, V850_INSTR_MAXLEN - 1, "0x%x[r%d], r%d",
				word2 & 0xFFFE, get_reg1 (word1), get_reg2 (word1));
		break;
	case V850_STHW:
		snprintf (cmd->instr, V850_INSTR_MAXLEN - 1, "%s.%c",
				instrs[get_opcode (word1)], word2 & 1 ? 'w' : 'h');
		snprintf (cmd->operands, V850_INSTR_MAXLEN - 1, "r%d, 0x%x[r%d]",
			       get_reg2 (word1), word2 & 0xFFFE, get_reg1 (word1));
		break;
	}

	return 4;
}