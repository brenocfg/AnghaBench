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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int numOperands; int opcodeMask; scalar_t__* operandTypes; int /*<<< orphan*/ * operandMasks; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int MAX_TOKEN_SIZE ; 
 scalar_t__ OPERAND_LONG_ABSOLUTE_ADDRESS ; 
 scalar_t__ OPERAND_REGISTER_GHOST ; 
 int /*<<< orphan*/  TOKEN_DELIM ; 
 scalar_t__ assemble_operand (int /*<<< orphan*/ *,char*,scalar_t__,int*) ; 
 TYPE_2__* instructionSet ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int packDataByMask (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setbin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int search_instruction (int /*<<< orphan*/ *,char**,unsigned int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *ao, const char *str) {
	char tokens[3][MAX_TOKEN_SIZE];
	char *token;
	uint32_t coded = 0;
	int len  = 0;
	uint32_t op1 = 0, op2 = 0;
	unsigned int tokens_cnt = 0;
	int instr_idx = -1;

	// simple tokenizer -- creates an array of maximum three tokens
	// the delimiters are ' ' and ','
	token = strtok ((char *)str, TOKEN_DELIM);
	while (token != NULL && tokens_cnt < 3) {
		memset (tokens[tokens_cnt], 0, MAX_TOKEN_SIZE);
		strncpy (tokens[tokens_cnt], token, MAX_TOKEN_SIZE-1);
		token = strtok (NULL, TOKEN_DELIM);
		tokens_cnt += 1;
	}

	if (tokens_cnt > 0) {
		// find nearest instruction that looks like supplied
		instr_idx = search_instruction (a, tokens, tokens_cnt - 1);

		if (instr_idx >= 0) {
			// no operands -- just return opcode mask
			if (instructionSet[instr_idx].numOperands == 0 && tokens_cnt == 1) {
				coded = instructionSet[instr_idx].opcodeMask;
				len = 2;
			/* for 1 or 2 operands (args) there are two cases:
			   1) for 2-byte instruction we use following scheme:
				mask | (packed first operand) [| (packed second operand)]
				packing is done by predefind operator mask
			   2) for 4-byte instruction we:
			 	get first 6 bits of long operand and masking them in the same way as (1)
				ORing with the last 16 bits(/2 for jmp/call) */
			} else if (instructionSet[instr_idx].numOperands == 1 && tokens_cnt == 2) {

				if (assemble_operand (a, tokens[1], instructionSet[instr_idx].operandTypes[0], &op1) >= 0) {
					// jmp and call has 4-byte opcode
					if (instructionSet[instr_idx].operandTypes[0] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
						op1 = op1/2;
						coded = instructionSet[instr_idx].opcodeMask
						| packDataByMask((op1 >> 16), instructionSet[instr_idx].operandMasks[0]);
						// memory addressed in bytes for jumps
						coded |= ((uint16_t)op1) << 16;
						len = 4;
					} else {
						// see avr_disasm.h for OPERAND_REGISTER_GHOST description
						// e.g. clr r0 == eor r0, r0
						if (instructionSet[instr_idx].operandTypes[1] == OPERAND_REGISTER_GHOST) {
							coded = instructionSet[instr_idx].opcodeMask
							| packDataByMask(op1, instructionSet[instr_idx].operandMasks[0])
							| packDataByMask(op1, instructionSet[instr_idx].operandMasks[1]);
						} else {
							coded = instructionSet[instr_idx].opcodeMask
							| packDataByMask(op1, instructionSet[instr_idx].operandMasks[0]);
						}

						len = 2;
					}
				}

			} else if (instructionSet[instr_idx].numOperands == 2 && tokens_cnt == 3) {
				if (assemble_operand(a, tokens[1], instructionSet[instr_idx].operandTypes[0], &op1) >= 0 &&
				   assemble_operand(a, tokens[2], instructionSet[instr_idx].operandTypes[1], &op2) >= 0) {

					coded = instructionSet[instr_idx].opcodeMask
						| packDataByMask(op1, instructionSet[instr_idx].operandMasks[0])
						| packDataByMask(op2, instructionSet[instr_idx].operandMasks[1]);

					len = 2;

					// handling lds/sts instructions
					if (instructionSet[instr_idx].operandTypes[0] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
						coded |= ((uint16_t)op1) << 16;
						len = 4;
					} else if (instructionSet[instr_idx].operandTypes[1] == OPERAND_LONG_ABSOLUTE_ADDRESS) {
						coded |= ((uint16_t)op2) << 16;
						len = 4;
					}
				}
			}
		}
	}

	// copying result to radare struct
	if (len > 0) {
		r_strbuf_setbin (&ao->buf, (const ut8*)&coded, len);
	}
	return len;
}