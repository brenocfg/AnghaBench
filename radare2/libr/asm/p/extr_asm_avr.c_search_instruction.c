#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* mnemonic; int numOperands; int opcodeMask; scalar_t__* operandTypes; } ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int AVR_TOTAL_INSTRUCTIONS ; 
 int /*<<< orphan*/  MAX_TOKEN_SIZE ; 
 scalar_t__ OPERAND_LONG_ABSOLUTE_ADDRESS ; 
 int getnum (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* instructionSet ; 
 scalar_t__ parse_specialreg (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int search_instruction(RAsm *a, char instr[3][MAX_TOKEN_SIZE], int args) {
	int i, op1 = 0, op2 = 0;

	for (i = 0; i < AVR_TOTAL_INSTRUCTIONS - 1; i++) {
		// check instruction mnemonic
		if (!strncmp (instr[0], instructionSet[i].mnemonic, MAX_TOKEN_SIZE)) {
			// in AVR instructions could have different opcodes based on number of arguments
			if (instructionSet[i].numOperands == args) {
				/* because st Z+ and st Z (and so on...) are instructions with DIFFERENT opcodes
				   we handling all this instruction manually, by pre-parsing the arguments */
				if (args != 2) {
					return i; // it's 0- or 1- arg instruction
				}
				// handling (e)lpm instruction with 2 args
				if (instructionSet[i].opcodeMask >= 0x9004 &&
					instructionSet[i].opcodeMask <= 0x9007) {
					if (instructionSet[i].operandTypes[1] == parse_specialreg (instr[2])) {
						return i;
					}
					// handling ld & ldd instruction with 2 args
				} else if (instructionSet[i].mnemonic[0] == 'l'
					&& instructionSet[i].mnemonic[1] == 'd'
					&& (instructionSet[i].mnemonic[2] == 'd' || instructionSet[i].mnemonic[2] == '\0')) {
					if (instructionSet[i].operandTypes[1] == parse_specialreg (instr[2])) {
						return i;
					}
					// handling lds command, distinguishing long from 16-bit version
				} else if (instructionSet[i].mnemonic[0] == 'l'
					&& instructionSet[i].mnemonic[1] == 'd'
					&& instructionSet[i].mnemonic[2] == 's'
					&& instructionSet[i].operandTypes[1] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
					// ineffective, but needed for lds/sts and other cases
					if (strlen(instr[2]) > 0) {
						op2 = getnum (a, instr[2]);
						if (op2 > 127) {
							return i;
						}
					}
				// handling st & std instruction with 2 args
				} else if (instructionSet[i].mnemonic[0] == 's'
					&& instructionSet[i].mnemonic[1] == 't'
					&& (instructionSet[i].mnemonic[2] == 'd' || instructionSet[i].mnemonic[2] == '\0')) {

					if (instructionSet[i].operandTypes[0] == parse_specialreg (instr[1])) {
						return i;
					}
					// handling sts long command
				} else if (instructionSet[i].mnemonic[0] == 's'
					&& instructionSet[i].mnemonic[1] == 't'
					&& instructionSet[i].mnemonic[2] == 's'
					&& instructionSet[i].operandTypes[0] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
					// same for 1st operand of sts
					if (strlen(instr[1]) > 0) {
						op1 = getnum (a, instr[1]);
						if (op1 > 127) {
							return i;
						}
					}
				} else {
					return i; // it's not st/ld/lpm-like instruction with 2 args
				}
			}
		}
	}
	return -1;
}