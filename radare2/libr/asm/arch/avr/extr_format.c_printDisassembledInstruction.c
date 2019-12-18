#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  formattingOptions ;
struct TYPE_6__ {TYPE_1__* instruction; } ;
typedef  TYPE_2__ disassembledInstruction ;
struct TYPE_5__ {char* mnemonic; int numOperands; } ;

/* Variables and functions */
 scalar_t__ AVR_LONG_INSTRUCTION_FOUND ; 
 scalar_t__ AVR_Long_Instruction ; 
 int formatDisassembledOperand (char*,int,TYPE_2__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int printDisassembledInstruction(char *out, const disassembledInstruction dInstruction, formattingOptions fOptions) {
	//char fmt[64];
	int retVal, i;
	char strOperand[256];
	*out = '\0';

	/* If we just found a long instruction, there is nothing to be printed yet, since we don't
	 * have the entire long address ready yet. */
	if (AVR_Long_Instruction == AVR_LONG_INSTRUCTION_FOUND)
		return 0;

	strcat (out, dInstruction.instruction->mnemonic);
	if (dInstruction.instruction->numOperands > 0)
		strcat (out, " ");

	for (i = 0; i < dInstruction.instruction->numOperands; i++) {
		/* If we're not on the first operand, but not on the last one either, print a comma separating
		 * the operands. */
		if (i > 0 && i != dInstruction.instruction->numOperands)
			strcat (out, ", ");
		/* Format the disassembled operand into the string strOperand, and print it */
		retVal = formatDisassembledOperand(strOperand, i, dInstruction, fOptions);
		if (retVal < 0)
			return retVal;
		/* Print the operand and free if it's not NULL */
		strcat (out, strOperand);
	}

	return 1;
}