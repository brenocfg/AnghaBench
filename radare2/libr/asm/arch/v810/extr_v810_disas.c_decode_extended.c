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
typedef  int /*<<< orphan*/  ut16 ;
struct v810_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int OPCODE (int /*<<< orphan*/  const) ; 
 int REG1 (int /*<<< orphan*/  const) ; 
 int REG2 (int /*<<< orphan*/  const) ; 
#define  V810_EXT_ADDF_S 139 
#define  V810_EXT_CMPF_S 138 
#define  V810_EXT_CVT_SW 137 
#define  V810_EXT_CVT_WS 136 
#define  V810_EXT_DIVF_S 135 
#define  V810_EXT_MPYHW 134 
#define  V810_EXT_MULF_S 133 
#define  V810_EXT_REV 132 
#define  V810_EXT_SUBF_S 131 
#define  V810_EXT_TRNC_SW 130 
#define  V810_EXT_XB 129 
#define  V810_EXT_XH 128 
 scalar_t__ V810_INSTR_MAXLEN ; 
 char** ext_instrs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_extended(const ut16 word1, const ut16 word2, struct v810_cmd *cmd) {
	ut8 subop = OPCODE(word2);
	if (subop > 0xC) {
		return -1;
	}

	snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "%s",
			ext_instrs[subop]);

	switch (subop) {
	case V810_EXT_CMPF_S:
	case V810_EXT_CVT_WS:
	case V810_EXT_CVT_SW:
	case V810_EXT_ADDF_S:
	case V810_EXT_SUBF_S:
	case V810_EXT_MULF_S:
	case V810_EXT_DIVF_S:
	case V810_EXT_REV:
	case V810_EXT_TRNC_SW:
	case V810_EXT_MPYHW:
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "r%d, r%d",
				REG1(word1), REG2(word1));
		break;
	case V810_EXT_XB:
	case V810_EXT_XH:
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "r%d",
				REG2(word1));
		break;
	default:
		return -1;
	}

	return 4;
}