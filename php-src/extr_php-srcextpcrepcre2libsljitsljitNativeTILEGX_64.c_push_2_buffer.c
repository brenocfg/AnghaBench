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
struct tilegx_opcode {char* name; } ;
struct sljit_compiler {int dummy; } ;
typedef  int /*<<< orphan*/  sljit_s32 ;
struct TYPE_2__ {int* operand_value; int line; long input_registers; long output_registers; int /*<<< orphan*/  pipe; struct tilegx_opcode const* opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 int /*<<< orphan*/  SLJIT_UNREACHABLE () ; 
 size_t TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE ; 
#define  TILEGX_OPC_BEQZ 141 
#define  TILEGX_OPC_BNEZ 140 
#define  TILEGX_OPC_CLZ 139 
#define  TILEGX_OPC_LD 138 
#define  TILEGX_OPC_LD1S 137 
#define  TILEGX_OPC_LD1U 136 
#define  TILEGX_OPC_LD2S 135 
#define  TILEGX_OPC_LD2U 134 
#define  TILEGX_OPC_LD4S 133 
#define  TILEGX_OPC_LD4U 132 
#define  TILEGX_OPC_ST 131 
#define  TILEGX_OPC_ST1 130 
#define  TILEGX_OPC_ST2 129 
#define  TILEGX_OPC_ST4 128 
 int /*<<< orphan*/  get_any_valid_pipe (struct tilegx_opcode const*) ; 
 TYPE_1__* inst_buf ; 
 size_t inst_buf_index ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct tilegx_opcode* tilegx_opcodes ; 
 int /*<<< orphan*/  update_buffer (struct sljit_compiler*) ; 

__attribute__((used)) static sljit_s32 push_2_buffer(struct sljit_compiler *compiler, tilegx_mnemonic opc, int op0, int op1, int line)
{
	if (inst_buf_index == TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE)
		FAIL_IF(update_buffer(compiler));

	const struct tilegx_opcode* opcode = &tilegx_opcodes[opc];
	inst_buf[inst_buf_index].opcode = opcode;
	inst_buf[inst_buf_index].pipe = get_any_valid_pipe(opcode);
	inst_buf[inst_buf_index].operand_value[0] = op0;
	inst_buf[inst_buf_index].operand_value[1] = op1;
	inst_buf[inst_buf_index].line = line;

	switch (opc) {
	case TILEGX_OPC_BEQZ:
	case TILEGX_OPC_BNEZ:
		inst_buf[inst_buf_index].input_registers = 1L << op0;
		break;
	case TILEGX_OPC_ST:
	case TILEGX_OPC_ST1:
	case TILEGX_OPC_ST2:
	case TILEGX_OPC_ST4:
		inst_buf[inst_buf_index].input_registers = (1L << op0) | (1L << op1);
		inst_buf[inst_buf_index].output_registers = 0;
		break;
	case TILEGX_OPC_CLZ:
	case TILEGX_OPC_LD:
	case TILEGX_OPC_LD1U:
	case TILEGX_OPC_LD1S:
	case TILEGX_OPC_LD2U:
	case TILEGX_OPC_LD2S:
	case TILEGX_OPC_LD4U:
	case TILEGX_OPC_LD4S:
		inst_buf[inst_buf_index].input_registers = 1L << op1;
		inst_buf[inst_buf_index].output_registers = 1L << op0;
		break;
	default:
		printf("unrecoginzed opc: %s\n", opcode->name);
		SLJIT_UNREACHABLE();
	}

	inst_buf_index++;

	return SLJIT_SUCCESS;
}