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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int ut16 ;
struct propeller_cmd {int dst; int src; int immed; int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROP_INSTR_MAXLEN ; 
#define  PROP_JMP 128 
 int get_dst (int /*<<< orphan*/ ) ; 
 int get_opcode (int /*<<< orphan*/ ) ; 
 int get_src (int /*<<< orphan*/ ) ; 
 int get_zcri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int decode_jmp (struct propeller_cmd *cmd, ut32 instr) {
	ut16 opcode;
	ut8 zcri;
	int ret = 1;
	opcode = get_opcode (instr);
	switch (opcode) {
		case PROP_JMP:
			zcri = get_zcri (instr);
			if (zcri & 0x2) {
				snprintf (cmd->instr, PROP_INSTR_MAXLEN - 1,
						"%s", "jmpret");
				if (zcri & 1) {
					cmd->dst = get_dst (instr) << 2;
					cmd->src = get_src (instr) << 2;

					snprintf (cmd->operands, PROP_INSTR_MAXLEN - 1,
							"0x%x, #0x%x", get_dst (instr), get_src (instr) << 2);
				} else {
					cmd->src = get_src (instr) << 2;
					cmd->dst = get_dst (instr) << 2;
					snprintf (cmd->operands, PROP_INSTR_MAXLEN - 1,
							"0x%x, 0x%x", get_dst (instr), get_src (instr) << 2);
				}
			} else {
				snprintf (cmd->instr, PROP_INSTR_MAXLEN - 1,
						"%s", "jmp");
				if (zcri & 1) {
					cmd->src = get_src (instr) << 2;
					cmd->immed = 1;
					snprintf (cmd->operands, PROP_INSTR_MAXLEN - 1,
							"#0x%x", get_src (instr) << 2);
				} else {
					cmd->immed = 0;
					cmd->src = get_src (instr) << 2; 
					snprintf (cmd->operands, PROP_INSTR_MAXLEN - 1,
							"0x%x", get_src (instr) << 2);
				}
			}

			ret = 4;
			break;
	}


	return ret;
}