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
typedef  size_t tilegx_mnemonic ;
struct tilegx_opcode {int dummy; } ;
struct sljit_compiler {int dummy; } ;
typedef  int /*<<< orphan*/  sljit_s32 ;
struct TYPE_2__ {int* operand_value; long input_registers; long output_registers; int line; int /*<<< orphan*/  pipe; struct tilegx_opcode const* opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 size_t TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE ; 
 int /*<<< orphan*/  get_any_valid_pipe (struct tilegx_opcode const*) ; 
 TYPE_1__* inst_buf ; 
 size_t inst_buf_index ; 
 struct tilegx_opcode* tilegx_opcodes ; 
 int /*<<< orphan*/  update_buffer (struct sljit_compiler*) ; 

__attribute__((used)) static sljit_s32 push_4_buffer(struct sljit_compiler *compiler, tilegx_mnemonic opc, int op0, int op1, int op2, int op3, int line)
{
	if (inst_buf_index == TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE)
		FAIL_IF(update_buffer(compiler));

	const struct tilegx_opcode* opcode = &tilegx_opcodes[opc];
	inst_buf[inst_buf_index].opcode = opcode;
	inst_buf[inst_buf_index].pipe = get_any_valid_pipe(opcode);
	inst_buf[inst_buf_index].operand_value[0] = op0;
	inst_buf[inst_buf_index].operand_value[1] = op1;
	inst_buf[inst_buf_index].operand_value[2] = op2;
	inst_buf[inst_buf_index].operand_value[3] = op3;
	inst_buf[inst_buf_index].input_registers = 1L << op1;
	inst_buf[inst_buf_index].output_registers = 1L << op0;
	inst_buf[inst_buf_index].line = line;
	inst_buf_index++;

	return SLJIT_SUCCESS;
}