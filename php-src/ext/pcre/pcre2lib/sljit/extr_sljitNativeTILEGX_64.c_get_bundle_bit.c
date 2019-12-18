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
typedef  int /*<<< orphan*/  tilegx_bundle_bits ;
struct tilegx_operand {int /*<<< orphan*/  (* insert ) (int) ;} ;
struct tilegx_opcode {int num_operands; size_t** operands; int /*<<< orphan*/ * fixed_bit_values; } ;
struct jit_instr {size_t pipe; int* operand_value; struct tilegx_opcode* opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 
 struct tilegx_operand* tilegx_operands ; 

tilegx_bundle_bits get_bundle_bit(struct jit_instr *inst)
{
	int i, val;
	const struct tilegx_opcode* opcode = inst->opcode;
	tilegx_bundle_bits bits = opcode->fixed_bit_values[inst->pipe];

	const struct tilegx_operand* operand = NULL;
	for (i = 0; i < opcode->num_operands; i++) {
		operand = &tilegx_operands[opcode->operands[inst->pipe][i]];
		val = inst->operand_value[i];

		bits |= operand->insert(val);
	}

	return bits;
}