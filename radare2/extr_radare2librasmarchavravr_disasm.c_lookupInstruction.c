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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__* operandTypes; scalar_t__* operandMasks; scalar_t__ opcodeMask; } ;

/* Variables and functions */
 int AVR_MAX_NUM_OPERANDS ; 
 int AVR_TOTAL_INSTRUCTIONS ; 
 scalar_t__ OPERAND_REGISTER_GHOST ; 
 scalar_t__ extractDataFromMask (scalar_t__,scalar_t__) ; 
 TYPE_1__* instructionSet ; 

__attribute__((used)) static int lookupInstruction(uint16_t opcode, int offset) {
	uint16_t opcodeSearch, operandTemp;
	int insidx, ghostRegisterConfirmed, i, j;
	
	for (insidx = offset; insidx < AVR_TOTAL_INSTRUCTIONS; insidx++) {
		opcodeSearch = opcode;
		/* If we have a ghost register operand (OPERAND_REGISTER_GHOST),
		 * we need to confirm that all of the other register operands are the same */
		ghostRegisterConfirmed = 1;
		/* We want to mask out all of the operands. We don't count up to
		 * instructionSet[insidx].numOperands because some instructions,
		 * such as clr R16, are actually encoded with two operands (so as eor R16,R16),
		 * and we want to screen out both operands to get the most simplest form of 
		 * the instruction. */ 
		for (i = 0; i < AVR_MAX_NUM_OPERANDS; i++) {
			if (instructionSet[insidx].operandTypes[i] == OPERAND_REGISTER_GHOST) {
				/* Grab the first operand */
				operandTemp = extractDataFromMask(opcode, instructionSet[insidx].operandMasks[0]);
				/* Compare the remaining operands to the first */
				for (j = 1; j < AVR_MAX_NUM_OPERANDS; j++) {
					if (extractDataFromMask(opcode, instructionSet[insidx].operandMasks[i]) !=
							operandTemp)
						ghostRegisterConfirmed = 0;
				}
			} 
			opcodeSearch &= ~(instructionSet[insidx].operandMasks[i]);
		}
		/* If we encountered a ghost register and were unable confirm that
		 * all register operands were equal (in this case ghostRegisterConfirmed
		 * would have changed), then move the match-search onto the next instruction. */
		if (ghostRegisterConfirmed == 0)
			continue;

		if (opcodeSearch == instructionSet[insidx].opcodeMask) 
			break;
	}
	/* It's impossible not to find an instruction, because the last instruction ".DW",
	 * specifies a word of data at the addresses, instead of an instruction. 
	 * Its operand 2 mask, 0x0000, will set opcode search to 0x0000, and this will always
	 * match with the opcodeMask of 0x0000. */
	return insidx;
}