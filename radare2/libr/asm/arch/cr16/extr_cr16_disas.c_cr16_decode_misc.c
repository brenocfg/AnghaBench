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
struct cr16_cmd {char* operands; int /*<<< orphan*/  type; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
#define  CR16_DI 133 
#define  CR16_EI 132 
#define  CR16_EWAIT 131 
 int /*<<< orphan*/  CR16_INSTR_MAXLEN ; 
#define  CR16_NOP 130 
#define  CR16_RETX 129 
 int /*<<< orphan*/  CR16_TYPE_DI ; 
 int /*<<< orphan*/  CR16_TYPE_EI ; 
 int /*<<< orphan*/  CR16_TYPE_EWAIT ; 
 int /*<<< orphan*/  CR16_TYPE_EXCP ; 
 int /*<<< orphan*/  CR16_TYPE_NOP ; 
 int /*<<< orphan*/  CR16_TYPE_RETX ; 
 int /*<<< orphan*/  CR16_TYPE_WAIT ; 
#define  CR16_WAIT 128 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cr16_decode_misc(const ut8 *instr, struct cr16_cmd *cmd)
{
	ut16 c;
	int ret = 2;

	c = r_read_le16 (instr);

	cmd->operands[0] = '\0';
	switch (c) {
	case CR16_RETX:
		strncpy(cmd->instr, "retx", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_RETX;
		break;
	case CR16_DI:
		strncpy(cmd->instr, "di", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_DI;
		break;
	case CR16_EI:
		strncpy(cmd->instr, "ei", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_EI;
		break;
	case CR16_NOP:
		strncpy(cmd->instr, "nop", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_NOP;
		break;
	case CR16_WAIT:
		strncpy(cmd->instr, "wait", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_WAIT;
		break;
	case CR16_EWAIT:
		strncpy(cmd->instr, "eiwait", CR16_INSTR_MAXLEN - 1);
		cmd->type = CR16_TYPE_EWAIT;
		break;
	default:
		switch (c >> 5) {
		case 0x3DF:
			strncpy(cmd->instr, "excp", CR16_INSTR_MAXLEN - 1);
			snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
					"0x%x", (c >> 1) & 0xF);
			cmd->type = CR16_TYPE_EXCP;
			break;
		default:
			ret = -1;
		}
	}

	return ret;
}