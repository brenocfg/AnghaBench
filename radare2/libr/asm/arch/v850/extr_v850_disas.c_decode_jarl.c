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
typedef  int ut8 ;
typedef  int ut32 ;
typedef  int ut16 ;
struct v850_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 scalar_t__ V850_INSTR_MAXLEN ; 
 size_t get_opcode (int) ; 
 int get_reg1 (int) ; 
 int get_reg2 (int) ; 
 char** instrs ; 
 int r_read_at_le16 (int const*,int) ; 
 int r_read_le16 (int const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_jarl(const ut8 *instr, int len, struct v850_cmd *cmd) {
	if (len < 4) {
		return -1;
	}

	ut16 word1 = r_read_le16 (instr);
	ut16 word2 = r_read_at_le16 (instr, 2);

	ut8 reg = get_reg2 (word1);
	ut32 disp = (word2 << 6) | get_reg1 (word1);

	snprintf (cmd->instr, V850_INSTR_MAXLEN - 1, "%s", instrs[get_opcode (word1)]);
	snprintf (cmd->operands, V850_INSTR_MAXLEN - 1, "0x%08x, r%d",
			disp << 1, reg);

	return 4;
}