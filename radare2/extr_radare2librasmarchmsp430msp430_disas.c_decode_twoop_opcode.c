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
typedef  size_t ut8 ;
typedef  int /*<<< orphan*/  ut16 ;
struct msp430_cmd {size_t opcode; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int decode_addressing_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msp430_cmd*) ; 
 scalar_t__ get_bw (int /*<<< orphan*/ ) ; 
 size_t get_twoop_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncat (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char** two_op_instrs ; 

__attribute__((used)) static int decode_twoop_opcode(ut16 instr, ut16 op1, ut16 op2, struct msp430_cmd *cmd)
{
	ut8 opcode = get_twoop_opcode(instr);

	snprintf (cmd->instr, sizeof (cmd->instr), "%s", two_op_instrs[opcode]);
	if (get_bw (instr)) {
		strncat (cmd->instr, ".b", sizeof (cmd->instr) - 1 - strlen(cmd->instr));
	}

	cmd->opcode = opcode;
	return decode_addressing_mode (instr, op1, op2, cmd);
}