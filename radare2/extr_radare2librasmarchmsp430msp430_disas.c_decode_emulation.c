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
typedef  scalar_t__ ut8 ;
typedef  int /*<<< orphan*/  ut16 ;
struct msp430_cmd {char* instr; char* operands; int /*<<< orphan*/  opcode; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ MSP430_ADD ; 
 scalar_t__ MSP430_ADDC ; 
 scalar_t__ MSP430_BIC ; 
 scalar_t__ MSP430_BIS ; 
 scalar_t__ MSP430_CMP ; 
 scalar_t__ MSP430_DADD ; 
 scalar_t__ MSP430_MOV ; 
 int /*<<< orphan*/  MSP430_ONEOP ; 
 scalar_t__ MSP430_PC ; 
 scalar_t__ MSP430_R3 ; 
 int /*<<< orphan*/  MSP430_RETI ; 
 scalar_t__ MSP430_SP ; 
 scalar_t__ MSP430_SR ; 
 scalar_t__ MSP430_SUB ; 
 scalar_t__ MSP430_SUBC ; 
 scalar_t__ MSP430_XOR ; 
 scalar_t__ get_ad (int /*<<< orphan*/ ) ; 
 scalar_t__ get_as (int /*<<< orphan*/ ) ; 
 scalar_t__ get_bw (int /*<<< orphan*/ ) ; 
 scalar_t__ get_dst (int /*<<< orphan*/ ) ; 
 scalar_t__ get_src (int /*<<< orphan*/ ) ; 
 scalar_t__ get_twoop_opcode (int /*<<< orphan*/ ) ; 
 char** msp430_register_names ; 
 int /*<<< orphan*/  remove_first_operand (struct msp430_cmd*) ; 
 int /*<<< orphan*/  remove_second_operand (struct msp430_cmd*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_emulation(ut16 instr, struct msp430_cmd *cmd)
{
	int ret = -1;
	ut8 as, ad, src, dst, bw, opcode;

	as = get_as(instr);
	ad = get_ad(instr);
	src = get_src(instr);
	dst = get_dst(instr);
	bw = get_bw(instr);
	opcode = get_twoop_opcode(instr);

	if (opcode == MSP430_ADDC && as == 0 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "adc.b" : "adc");
		snprintf(cmd->operands, sizeof (cmd->operands), "%s", msp430_register_names[dst]);
	} else if (opcode == MSP430_MOV && as == 0 && src == MSP430_R3) {
		if (ad == 0 && dst == MSP430_R3) {
			snprintf(cmd->instr, sizeof (cmd->instr), "nop");
			cmd->operands[0] = '\0';
		} else {
			snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "clr.b" : "clr");
			remove_first_operand(cmd);
		}
	} else if (opcode == MSP430_MOV && as == 3 && src == MSP430_SP) {
		if (dst == MSP430_PC) {
			snprintf(cmd->instr, sizeof (cmd->instr), "ret");
       			cmd->type = MSP430_ONEOP;
			cmd->opcode = MSP430_RETI;
			cmd->operands[0] = '\0';
		} else {
			snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "pop.b" : "pop");
			remove_first_operand(cmd);
		}
	} else if (opcode == MSP430_MOV && ad == 0 && dst == MSP430_PC) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", "br");
		remove_second_operand(cmd);
	} else if (opcode == MSP430_BIC && as == 2 && src == MSP430_SR && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", "clrn");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_BIC && as == 2 && src == MSP430_R3 && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", "clrz");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_BIC && as == 3 && src == MSP430_SR && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", "dint");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_BIS && as == 3 && src == MSP430_SR && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", "eint");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_DADD && as == 0 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "dadc.b" : "dadc");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_SUB && as == 1 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "dec.b" : "dec");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_SUB && as == 2 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "decd.b" : "decd");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_ADD && as == 1 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "inc.b" : "inc");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_ADD && as == 2 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "incd.b" : "incd");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_XOR && as == 3 && src == MSP430_R3) { 
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "inv.b" : "inv");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_ADD && src == dst) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "rla.b" : "rla");
		remove_second_operand(cmd);
	} else if (opcode == MSP430_ADDC && src == dst) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "rlc.b" : "rlc");
		remove_second_operand(cmd);
	} else if (opcode == MSP430_SUBC && as == 0 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "sbc.b" : "sbc");
		remove_first_operand(cmd);
	} else if (opcode == MSP430_BIS && as == 1 && src == MSP430_R3 && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "setc");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_BIS && as == 2 && src == MSP430_SR && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "setn");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_BIS && as == 2 && src == MSP430_R3 && dst == MSP430_SR && ad == 0) {
		snprintf(cmd->instr, sizeof (cmd->instr), "setz");
		cmd->operands[0] = '\0';
	} else if (opcode == MSP430_CMP && as == 0 && src == MSP430_R3) {
		snprintf(cmd->instr, sizeof (cmd->instr), "%s", bw ? "tst.b" : "tst");
		remove_first_operand(cmd);
	}

	return ret;
}