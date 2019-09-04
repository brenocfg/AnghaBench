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
typedef  int ut16 ;
struct msp430_cmd {char* operands; } ;
typedef  int /*<<< orphan*/  dstbuf ;

/* Variables and functions */
#define  MSP430_PC 130 
#define  MSP430_R3 129 
#define  MSP430_SR 128 
 int /*<<< orphan*/  decode_emulation (int,struct msp430_cmd*) ; 
 int get_ad (int) ; 
 int get_as (int) ; 
 int get_dst (int) ; 
 int get_src (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char** msp430_register_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,scalar_t__) ; 

__attribute__((used)) static int decode_addressing_mode(ut16 instr, ut16 op1, ut16 op2, struct msp430_cmd *cmd)
{
	int ret = 0, srcOperInCodeWord = 0;
	ut8 as, ad, src, dst;
	ut16 op;
	char dstbuf[16];

	memset(dstbuf, 0, sizeof(dstbuf));

	as = get_as(instr);
	ad = get_ad(instr);
	src = get_src(instr);
	dst = get_dst(instr);

	/* addressing mode of source operand */
	switch (as) {
	case 0:
		switch (src) {
		case MSP430_R3: /* CG2 */
			snprintf(cmd->operands, sizeof (cmd->operands), "#0");
			break;
		default: /* register mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "%s", msp430_register_names[src]);
		}
		ret = 2;
		break;
	case 1:
		ret = 4;
		switch (src) {
		case MSP430_PC: /* symbolic mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "0x%04x", op1);
			srcOperInCodeWord = 1;
			break;
		case MSP430_R3: /* CG2 */
			snprintf(cmd->operands, sizeof (cmd->operands), "%s", "#1");
			ret = 2;
			break;
		case MSP430_SR: /* absolute mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "&0x%04x", op1);
			srcOperInCodeWord = 1;
			break;
		default: /* indexed mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "0x%x(%s)", op1, msp430_register_names[src]);
			srcOperInCodeWord = 1;
		}
		break;
	case 2:
		switch (src) {
		case MSP430_SR: /* CG1 */
			snprintf(cmd->operands, sizeof (cmd->operands), "#4");
			break;
		case MSP430_R3: /* CG2 */
			snprintf(cmd->operands, sizeof (cmd->operands), "#2");
			break;
		default: /* indirect register mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "@%s", msp430_register_names[src]);
		}
		ret = 2;
		break;
	case 3:
		ret = 2;
		switch (src) {
		case MSP430_SR: /* CG1 */
			snprintf(cmd->operands, sizeof (cmd->operands), "#8");
			break;
		case MSP430_R3: /* CG2 */
			snprintf(cmd->operands, sizeof (cmd->operands), "#-1");
			break;
		case MSP430_PC: /* immediate mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "#0x%04x", op1);
			srcOperInCodeWord = 1;
			ret = 4;
			break;
		default: /* indirect autoincrement mode */
			snprintf(cmd->operands, sizeof (cmd->operands), "@%s+", msp430_register_names[src]);
		}
		break;
	}

	/* addressing mode of destination operand */
	switch (ad) {
	case 0: /* register mode */
		snprintf(dstbuf, sizeof (dstbuf), ", %s", msp430_register_names[dst]); 
		break;
	case 1:
		/* check addr. mode of source operand */
		if (srcOperInCodeWord != 0) {
		    op = op2;
		    ret = 6;
		} else {
		    op = op1;
		    ret = 4;
		}
		switch (get_dst(instr)) {
		case MSP430_PC: /* symbolic mode */
			snprintf(dstbuf, sizeof (dstbuf), ", 0x%04x", op);
			break;
		case MSP430_SR: /* absolute mode */
		    	snprintf(dstbuf, sizeof (dstbuf), ", &0x%04x", op);
			break;
		default: /* indexed mode */
			snprintf(dstbuf, sizeof (dstbuf), ", 0x%x(%s)", op, msp430_register_names[dst]);
		}
		break;
	}

	strncat(cmd->operands, dstbuf, sizeof (cmd->operands) - 1 - strlen(cmd->operands));
	decode_emulation(instr, cmd);
	return ret;
}