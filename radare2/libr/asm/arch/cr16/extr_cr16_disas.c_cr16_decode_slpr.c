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
struct cr16_cmd {int /*<<< orphan*/  type; int /*<<< orphan*/  operands; scalar_t__* instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR16_INSTR_MAXLEN ; 
#define  CR16_LPR 129 
#define  CR16_SPR 128 
 int /*<<< orphan*/  CR16_TYPE_SLPR ; 
 size_t cr16_get_dstreg (int) ; 
 size_t cr16_get_srcreg (int) ; 
 char** cr16_regs_names ; 
 char** dedicated_regs ; 
 char** instrs_4bit ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_str_ncpy (scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int cr16_decode_slpr(const ut8 *instr, struct cr16_cmd *cmd) {
	int ret = 2;

	ut16 c = r_read_le16 (instr);

	const char *ins = instrs_4bit[c >> 9];
	if (ins) {
		r_str_ncpy (cmd->instr, ins, sizeof (cmd->instr) - 1);
	} else {
		*cmd->instr = 0;
	}

	switch (c >> 9) {
	case CR16_LPR:
		snprintf (cmd->operands, CR16_INSTR_MAXLEN - 1,
				"%s,%s",cr16_regs_names[cr16_get_srcreg(c)],
				dedicated_regs[cr16_get_dstreg(c)]);
		break;
	case CR16_SPR:
		snprintf (cmd->operands, CR16_INSTR_MAXLEN - 1,
				"%s,%s", dedicated_regs[cr16_get_dstreg(c)],
				cr16_regs_names[cr16_get_srcreg(c)]);
		break;
	}

	cmd->type = CR16_TYPE_SLPR;

	return ret;
}