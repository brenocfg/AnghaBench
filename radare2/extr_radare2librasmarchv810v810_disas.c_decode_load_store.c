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
typedef  int st16 ;

/* Variables and functions */
 int OPCODE (int /*<<< orphan*/  const) ; 
 int REG1 (int /*<<< orphan*/  const) ; 
 int REG2 (int /*<<< orphan*/  const) ; 
#define  V810_CAXI 140 
#define  V810_INB 139 
#define  V810_INH 138 
 scalar_t__ V810_INSTR_MAXLEN ; 
#define  V810_INW 137 
#define  V810_LDB 136 
#define  V810_LDH 135 
#define  V810_LDW 134 
#define  V810_OUTB 133 
#define  V810_OUTH 132 
#define  V810_OUTW 131 
#define  V810_STB 130 
#define  V810_STH 129 
#define  V810_STW 128 
 char** instrs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_load_store(const ut16 word1, const ut16 word2, struct v810_cmd *cmd) {
	snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "%s",
		instrs[OPCODE(word1)]);

	switch (OPCODE(word1)) {
	case V810_STB:
	case V810_STH:
	case V810_STW:
	case V810_OUTB:
	case V810_OUTH:
	case V810_OUTW:
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1,
				"r%d, %hd[r%d]",
				REG2(word1), (st16)word2, REG1(word1));
		break;
	case V810_LDB:
	case V810_LDH:
	case V810_LDW:
	case V810_INB:
	case V810_INH:
	case V810_INW:
	case V810_CAXI:
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1,
				"%hd[r%d], r%d",
				(st16)word2, REG1(word1), REG2(word1));
		break;
	}

	return 4;
}