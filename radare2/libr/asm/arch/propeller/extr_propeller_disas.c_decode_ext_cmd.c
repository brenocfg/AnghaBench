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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int ut16 ;
struct propeller_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
#define  PROP_CLKSET 135 
#define  PROP_COGID 134 
#define  PROP_COGINIT 133 
#define  PROP_COGSTOP 132 
 int /*<<< orphan*/  PROP_INSTR_MAXLEN ; 
#define  PROP_LOCKCLR 131 
#define  PROP_LOCKNEW 130 
#define  PROP_LOCKRET 129 
#define  PROP_LOCKSET 128 
 char** ext_instrs ; 
 int get_dst (int /*<<< orphan*/ ) ; 
 int get_opcode_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int decode_ext_cmd (struct propeller_cmd *cmd, ut32 instr) {
	ut16 opcode;

	opcode = get_opcode_ext (instr);

	switch (opcode) {
		case PROP_CLKSET:
		case PROP_COGID:
		case PROP_COGINIT:
		case PROP_COGSTOP:
		case PROP_LOCKCLR:
		case PROP_LOCKNEW:
		case PROP_LOCKRET:
		case PROP_LOCKSET:
			snprintf (cmd->instr, PROP_INSTR_MAXLEN - 1,
					"%s", ext_instrs[PROP_CLKSET]);
			snprintf (cmd->operands, PROP_INSTR_MAXLEN - 1,
					"%d", get_dst (instr));
			return 4;
			break;
	}

	return -1;
}