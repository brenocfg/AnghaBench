#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* operands; TYPE_1__* instruction; } ;
typedef  TYPE_2__ disassembledInstruction ;
struct TYPE_4__ {int numOperands; int* operandTypes; } ;

/* Variables and functions */
 int ERROR_INVALID_ARGUMENTS ; 
#define  OPERAND_BRANCH_ADDRESS 133 
#define  OPERAND_COMPLEMENTED_DATA 132 
#define  OPERAND_REGISTER_EVEN_PAIR 131 
#define  OPERAND_REGISTER_EVEN_PAIR_STARTR24 130 
#define  OPERAND_REGISTER_STARTR16 129 
#define  OPERAND_RELATIVE_ADDRESS 128 

__attribute__((used)) static int disassembleOperands(disassembledInstruction *dInstruction) {
	int i;
	
	/* This should never happen */
	if (!dInstruction)
		return ERROR_INVALID_ARGUMENTS;
	if (!dInstruction->instruction)
		return ERROR_INVALID_ARGUMENTS;
	
	/* For each operand, decode its original value. */
	for (i = 0; i < dInstruction->instruction->numOperands; i++) {
		switch (dInstruction->instruction->operandTypes[i]) {
		case OPERAND_BRANCH_ADDRESS:
			/* K is 7 bits, so maximum value it can store is 127 decimal.
			 * However, a branch's operand, -64 <= k <= +63,
			 * can go 64 back (-64) or 63 forward (+63). Range: 64+63 = 127.
			 * In order to preserve the negative, the branch distance
			 * is stored in two's complement form.*/
			/* First we multiply by two, because every instruction is 2 bytes,
			 * so in order to branch to the right address (which increments by
			 * two for every instruction), we must multiply this distance
			 * by two. */
			/* Next, we check for the signed bit (MSB), which would indicate a
			 * negative. If the number is signed, we would reverse the two's
			 * complement (invert bits, add 1, and then only use the 7 bits that 
			 * matter), otherwise, the number represents a positive distance and
			 * no bit manipulation is necessary. */
			dInstruction->operands[i] <<= 1;
			if (dInstruction->operands[i] & 0x80) {
				/* We can't just print out the signed operand because the type's capacity
				 * is 16 bits, and the operand data's signedness only starts at 0x80.
				 * Therefore we must convert to the positive value and then make the entire
				 * short negative. */
				dInstruction->operands[i] = (~dInstruction->operands[i]+1)&0x7F;
				dInstruction->operands[i] = -dInstruction->operands[i]+2;
			} else {
				dInstruction->operands[i] += 2;
			}
			break;
		case OPERAND_RELATIVE_ADDRESS:
			/* k is 12 bits, so maximum value it can store is 4095 decimal.
			 * However, a relative jump/call's operand, -2K <= k < +2K,
			 * can go 2048 back (-2048) or 2047 forward (+2047). Range: 2048+2047 = 4095.
			 * In order to preserve the negative, the jump/call distance
			 * is stored in two's complement form.*/
			/* First we multiply by two, because every instruction is 2 bytes,
			 * so in order to jump/call to the right address (which increments by
			 * two for every instruction), we must multiply this distance
			 * by two. */
			/* Next, we check for the signed bit (MSB), which would indicate a
			 * negative. If the number is signed, we would reverse the two's
			 * complement (invert bits, add 1, and then only use the 12 bits that 
			 * matter), otherwise, the number represents a positive distance and
			 * no bit manipulation is necessary. */
			dInstruction->operands[i] <<= 1;
			if (dInstruction->operands[i] & 0x1000) {
				/* We can't just print out the signed operand because the type's capacity
				 * is 16 bits, and the operand data's signedness only starts at 0x1000.
				 * Therefore we must convert to the positive value and then make the entire
				 * short negative. */
				short val = ((~dInstruction->operands[i]) ) & 0xFFF;
				//dInstruction->operands[i] = (~dInstruction->operands[i])&0xFFF;
				dInstruction->operands[i] = -val + 1;
				//dInstruction->operands[i] += 2;
			} else {
				dInstruction->operands[i] += 2;
			}
			break;
		case OPERAND_REGISTER_STARTR16:
			dInstruction->operands[i] = 16 + dInstruction->operands[i] ;
			break;
		case OPERAND_REGISTER_EVEN_PAIR:
			dInstruction->operands[i] = dInstruction->operands[i] * 2;
			break;
		case OPERAND_REGISTER_EVEN_PAIR_STARTR24:
			dInstruction->operands[i] = 24 + (dInstruction->operands[i] * 2);
			break;
		case OPERAND_COMPLEMENTED_DATA:
			dInstruction->operands[i] = ~dInstruction->operands[i] & 0xFF;
			break;
		default:
			break;
		}
	}
	return 0;
}