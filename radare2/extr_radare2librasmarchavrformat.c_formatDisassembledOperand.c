#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int options; int /*<<< orphan*/  addressFieldWidth; } ;
typedef  TYPE_2__ formattingOptions ;
struct TYPE_8__ {int* operands; int address; TYPE_1__* instruction; } ;
typedef  TYPE_3__ disassembledInstruction ;
struct TYPE_6__ {int* operandTypes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR_Long_Address ; 
 int AVR_MAX_NUM_OPERANDS ; 
 int ERROR_MEMORY_ALLOCATION_ERROR ; 
 int ERROR_UNKNOWN_OPERAND ; 
 int FORMAT_OPTION_DATA_BIN ; 
 int FORMAT_OPTION_DATA_DEC ; 
#define  OPERAND_BIT 153 
#define  OPERAND_BRANCH_ADDRESS 152 
#define  OPERAND_COMPLEMENTED_DATA 151 
#define  OPERAND_DATA 150 
#define  OPERAND_DES_ROUND 149 
#define  OPERAND_IO_REGISTER 148 
#define  OPERAND_LONG_ABSOLUTE_ADDRESS 147 
#define  OPERAND_MX 146 
#define  OPERAND_MY 145 
#define  OPERAND_MZ 144 
#define  OPERAND_NONE 143 
 char* OPERAND_PREFIX_ABSOLUTE_ADDRESS ; 
 char* OPERAND_PREFIX_BIT ; 
 char* OPERAND_PREFIX_DATA_BIN ; 
 char* OPERAND_PREFIX_DATA_DEC ; 
 char* OPERAND_PREFIX_DATA_HEX ; 
 char* OPERAND_PREFIX_IO_REGISTER ; 
 char* OPERAND_PREFIX_REGISTER ; 
 char* OPERAND_PREFIX_WORD_DATA ; 
#define  OPERAND_REGISTER 142 
#define  OPERAND_REGISTER_EVEN_PAIR 141 
#define  OPERAND_REGISTER_EVEN_PAIR_STARTR24 140 
#define  OPERAND_REGISTER_GHOST 139 
#define  OPERAND_REGISTER_STARTR16 138 
#define  OPERAND_RELATIVE_ADDRESS 137 
#define  OPERAND_WORD_DATA 136 
#define  OPERAND_X 135 
#define  OPERAND_XP 134 
#define  OPERAND_Y 133 
#define  OPERAND_YP 132 
#define  OPERAND_YPQ 131 
#define  OPERAND_Z 130 
#define  OPERAND_ZP 129 
#define  OPERAND_ZPQ 128 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int formatDisassembledOperand(char *strOperand, int operandNum, const disassembledInstruction dInstruction, formattingOptions fOptions) {
	char binary[9];
	int retVal;

	if (operandNum >= AVR_MAX_NUM_OPERANDS)
		return 0;

	switch (dInstruction.instruction->operandTypes[operandNum]) {
	case OPERAND_NONE:
	case OPERAND_REGISTER_GHOST:
		strOperand = NULL;
		retVal = 0;
		break;
	case OPERAND_REGISTER:
	case OPERAND_REGISTER_STARTR16:
	case OPERAND_REGISTER_EVEN_PAIR_STARTR24:
	case OPERAND_REGISTER_EVEN_PAIR:
		retVal = sprintf (strOperand, "%s%d", OPERAND_PREFIX_REGISTER,
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_DATA:
	case OPERAND_COMPLEMENTED_DATA:
		if (fOptions.options & FORMAT_OPTION_DATA_BIN) {
			int i;
			for (i = 7; i >= 0; i--) {
				if (dInstruction.operands[operandNum] & (1<<i))
					binary[7-i] = '1';
				else
					binary[7-i] = '0';
			}
			binary[8] = '\0';
			retVal = sprintf(strOperand, "%s%s",
				OPERAND_PREFIX_DATA_BIN, binary);
		} else if (fOptions.options & FORMAT_OPTION_DATA_DEC) {
			retVal = sprintf(strOperand, "%s%d",
				OPERAND_PREFIX_DATA_DEC,
				dInstruction.operands[operandNum]);
		} else {
			retVal = sprintf(strOperand, "%s%02x",
				OPERAND_PREFIX_DATA_HEX,
				dInstruction.operands[operandNum]);
		}
		break;
	case OPERAND_BIT:
		retVal = sprintf(strOperand, "%s%d", OPERAND_PREFIX_BIT,
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_BRANCH_ADDRESS:
	case OPERAND_RELATIVE_ADDRESS:
#if 0
		/* If we have an address label, print it, otherwise just print the
		 * relative distance to the destination address. */
		if ((fOptions.options & FORMAT_OPTION_ADDRESS_LABEL) && fOptions.addressLabelPrefix != NULL) {
			retVal = sprintf(strOperand, "%s%0*X",
				fOptions.addressLabelPrefix,
				fOptions.addressFieldWidth,
				dInstruction.address+dInstruction.operands[operandNum]+2);
		} else {
#endif
#if 0
			/* Check if the operand is greater than 0 so we can print the + sign. */
			if (dInstruction.operands[operandNum] > 0) {
				//retVal = sprintf(strOperand, "%s+%d", OPERAND_PREFIX_BRANCH_ADDRESS, dInstruction.operands[operandNum]);
				//retVal = sprintf(strOperand, "%s+%d (0x%08x)", OPERAND_PREFIX_BRANCH_ADDRESS, dInstruction.operands[operandNum],
				//	dInstruction.address + dInstruction.operands[operandNum]);
				retVal = sprintf(strOperand, "0x%x", dInstruction.address + dInstruction.operands[operandNum]);
			} else {
			/* Since the operand variable is signed, the negativeness of the distance
			 * to the destination address has been taken care of in disassembleOperands() */
//					retVal = sprintf(strOperand, "%s%d", OPERAND_PREFIX_BRANCH_ADDRESS, dInstruction.operands[operandNum]);
			}
#endif
			retVal = sprintf(strOperand, "0x%x",
				dInstruction.address + dInstruction.operands[operandNum]);
		//}
		break;
	case OPERAND_LONG_ABSOLUTE_ADDRESS:
		retVal = sprintf(strOperand, "%s%0*x",
			OPERAND_PREFIX_ABSOLUTE_ADDRESS,
			fOptions.addressFieldWidth, AVR_Long_Address);
		break;
	case OPERAND_IO_REGISTER:
		retVal = sprintf(strOperand, "%s%02x",
			OPERAND_PREFIX_IO_REGISTER,
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_WORD_DATA:
		retVal = sprintf (strOperand, "%s%0*x",
			OPERAND_PREFIX_WORD_DATA,
			fOptions.addressFieldWidth,
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_DES_ROUND:
		retVal = sprintf (strOperand, "%s%02x",
			OPERAND_PREFIX_WORD_DATA,
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_YPQ:
		retVal = sprintf(strOperand, "y+%d",
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_ZPQ:
		retVal = sprintf(strOperand, "z+%d",
			dInstruction.operands[operandNum]);
		break;
	case OPERAND_X: retVal = sprintf(strOperand, "x"); break;
	case OPERAND_XP: retVal = sprintf(strOperand, "x+"); break;
	case OPERAND_MX: retVal = sprintf(strOperand, "-x"); break;
	case OPERAND_Y: retVal = sprintf(strOperand, "y"); break;
	case OPERAND_YP: retVal = sprintf(strOperand, "y+"); break;
	case OPERAND_MY: retVal = sprintf(strOperand, "-y"); break;
	case OPERAND_Z: retVal = sprintf(strOperand, "z"); break;
	case OPERAND_ZP: retVal = sprintf(strOperand, "z+"); break;
	case OPERAND_MZ: retVal = sprintf(strOperand, "-z"); break;
	/* This is impossible by normal operation. */
	default: return ERROR_UNKNOWN_OPERAND;
	}
	if (retVal < 0)
		return ERROR_MEMORY_ALLOCATION_ERROR;
	return 0;
}