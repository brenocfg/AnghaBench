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
typedef  int /*<<< orphan*/  ut16 ;
struct v810_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int DISP26 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 size_t OPCODE (int /*<<< orphan*/  const) ; 
 scalar_t__ V810_INSTR_MAXLEN ; 
 char** instrs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_jump(const ut16 word1, const ut16 word2, struct v810_cmd *cmd) {
	snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "%s",
			instrs[OPCODE(word1)]);
	snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "%d",
			DISP26(word1, word2));

	return 4;
}