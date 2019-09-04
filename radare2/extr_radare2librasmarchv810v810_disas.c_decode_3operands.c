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
typedef  int ut16 ;
struct v810_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  int st16 ;

/* Variables and functions */
 size_t OPCODE (int const) ; 
 int REG1 (int const) ; 
 int REG2 (int const) ; 
 size_t V810_ADDI ; 
 scalar_t__ V810_INSTR_MAXLEN ; 
 char** instrs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_3operands(const ut16 word1, const ut16 word2, struct v810_cmd *cmd) {
	snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "%s",
			instrs[OPCODE(word1)]);

	if (OPCODE(word1) == V810_ADDI) {
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "%d, r%d, r%d",
				(st16) word2, REG1(word1), REG2(word1));
	} else {
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "0x%x, r%d, r%d",
				word2, REG1(word1), REG2(word1));
	}

	return 4;
}