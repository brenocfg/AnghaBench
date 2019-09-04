#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* operands; TYPE_4__* instruction; int /*<<< orphan*/ * alternateInstruction; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ disassembledInstruction ;
struct TYPE_9__ {int opcode; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ assembledInstruction ;
struct TYPE_10__ {int numOperands; scalar_t__* operandTypes; int /*<<< orphan*/ * operandMasks; int /*<<< orphan*/  mnemonic; } ;

/* Variables and functions */
 scalar_t__ AVR_LONG_INSTRUCTION_FOUND ; 
 scalar_t__ AVR_LONG_INSTRUCTION_PRINT ; 
 int AVR_Long_Address ; 
 scalar_t__ AVR_Long_Instruction ; 
 int AVR_TOTAL_INSTRUCTIONS ; 
 int ERROR_INVALID_ARGUMENTS ; 
 scalar_t__ OPERAND_LONG_ABSOLUTE_ADDRESS ; 
 scalar_t__ disassembleOperands (TYPE_1__*) ; 
 int extractDataFromMask (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* instructionSet ; 
 TYPE_1__ longInstruction ; 
 int lookupInstruction (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int disassembleInstruction(disassembledInstruction *dInstruction, const assembledInstruction aInstruction) {
	int insidx, i;
	
	if (!dInstruction)
		return ERROR_INVALID_ARGUMENTS;
	
	
	/* Look up the instruction */
	insidx = lookupInstruction(aInstruction.opcode, 0);
	if (insidx == AVR_TOTAL_INSTRUCTIONS) {
		// invalid instruction
		return 0;
	}

	/*** AVR SPECIFIC */
	/* If a long instruction was found in the last instruction disassembly,
	 * extract the rest of the address, and indicate that it is to be printed */
	if (AVR_Long_Instruction == AVR_LONG_INSTRUCTION_FOUND) {
		AVR_Long_Instruction = AVR_LONG_INSTRUCTION_PRINT;
		AVR_Long_Address |= aInstruction.opcode;
		/* We must multiply by two, because every instruction is 2 bytes,
		 * so in order to jump/call to the right address (which increments by
		 * two for every instruction), we must multiply this distance by two. */
		//printf ("ii=%d\n", insidx);
                if(!strcmp(longInstruction.instruction->mnemonic,"call")||
                   !strcmp(longInstruction.instruction->mnemonic,"jmp"))
	        {
			AVR_Long_Address *= 2;
                }
		*dInstruction = longInstruction;
		return 0;
	/* If a long instruction was printed in the last instruction disassembly,
	 * reset the AVR_Call_Instruction variable back to zero. */
	} else if (AVR_Long_Instruction == AVR_LONG_INSTRUCTION_PRINT) {
		AVR_Long_Instruction = 0;
	}

	/* Copy over the address, and reference to the instruction, set
	 * the equivilant-encoded but different instruction to NULL for now. */
	dInstruction->address = aInstruction.address;
	dInstruction->instruction = &instructionSet[insidx];
	dInstruction->alternateInstruction = NULL;
	
	/* Copy out each operand, extracting the operand data from the original
	 * opcode using the operand mask. */
	for (i = 0; i < instructionSet[insidx].numOperands; i++) {
		dInstruction->operands[i] = extractDataFromMask(aInstruction.opcode, dInstruction->instruction->operandMasks[i]);
		/*** AVR SPECIFIC */
		/* If this is an instruction with a long absolute operand, indicate that a long instruction has been found,
		 * and extract the first part of the long address. */
		if (dInstruction->instruction->operandTypes[i] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
			AVR_Long_Instruction = AVR_LONG_INSTRUCTION_FOUND;
			AVR_Long_Address = dInstruction->operands[i] << 16;
			longInstruction = *dInstruction;
		}
	}
	
	/* Disassemble operands */
	if (disassembleOperands(dInstruction) < 0)
		return ERROR_INVALID_ARGUMENTS; /* Only possible error for disassembleOperands() */

	if (AVR_Long_Instruction == AVR_LONG_INSTRUCTION_FOUND) {
		/* If we found a long instruction (32-bit one),
		 * Copy this instruction over to our special longInstruction variable, that
		 * will exist even after we move onto the next 16-bits */
		longInstruction = *dInstruction;
	}

	return 0;
}