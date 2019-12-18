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
#define  TILEGX_OPC_ADD 152 
#define  TILEGX_OPC_ADDLI 151 
#define  TILEGX_OPC_AND 150 
#define  TILEGX_OPC_CMOVEQZ 149 
#define  TILEGX_OPC_CMOVNEZ 148 
#define  TILEGX_OPC_CMPLTS 147 
#define  TILEGX_OPC_CMPLTSI 146 
#define  TILEGX_OPC_CMPLTU 145 
#define  TILEGX_OPC_CMPLTUI 144 
#define  TILEGX_OPC_LD_ADD 143 
#define  TILEGX_OPC_MULX 142 
#define  TILEGX_OPC_NOR 141 
#define  TILEGX_OPC_OR 140 
#define  TILEGX_OPC_ORI 139 
#define  TILEGX_OPC_SHL 138 
#define  TILEGX_OPC_SHL16INSLI 137 
#define  TILEGX_OPC_SHLI 136 
#define  TILEGX_OPC_SHRS 135 
#define  TILEGX_OPC_SHRSI 134 
#define  TILEGX_OPC_SHRU 133 
#define  TILEGX_OPC_SHRUI 132 
#define  TILEGX_OPC_ST_ADD 131 
#define  TILEGX_OPC_SUB 130 
#define  TILEGX_OPC_XOR 129 
#define  TILEGX_OPC_XORI 128 
 int /*<<< orphan*/  get_any_valid_pipe (struct tilegx_opcode const*) ; 
 TYPE_1__* inst_buf ; 
 size_t inst_buf_index ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct tilegx_opcode* tilegx_opcodes ; 
 int /*<<< orphan*/  update_buffer (struct sljit_compiler*) ; 

__attribute__((used)) static sljit_s32 push_3_buffer(struct sljit_compiler *compiler, tilegx_mnemonic opc, int op0, int op1, int op2, int line)
{
	if (inst_buf_index == TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE)
		FAIL_IF(update_buffer(compiler));

	const struct tilegx_opcode* opcode = &tilegx_opcodes[opc];
	inst_buf[inst_buf_index].opcode = opcode;
	inst_buf[inst_buf_index].pipe = get_any_valid_pipe(opcode);
	inst_buf[inst_buf_index].operand_value[0] = op0;
	inst_buf[inst_buf_index].operand_value[1] = op1;
	inst_buf[inst_buf_index].operand_value[2] = op2;
	inst_buf[inst_buf_index].line = line;

	switch (opc) {
	case TILEGX_OPC_ST_ADD:
		inst_buf[inst_buf_index].input_registers = (1L << op0) | (1L << op1);
		inst_buf[inst_buf_index].output_registers = 1L << op0;
		break;
	case TILEGX_OPC_LD_ADD:
		inst_buf[inst_buf_index].input_registers = 1L << op1;
		inst_buf[inst_buf_index].output_registers = (1L << op0) | (1L << op1);
		break;
	case TILEGX_OPC_ADD:
	case TILEGX_OPC_AND:
	case TILEGX_OPC_SUB:
	case TILEGX_OPC_MULX:
	case TILEGX_OPC_OR:
	case TILEGX_OPC_XOR:
	case TILEGX_OPC_NOR:
	case TILEGX_OPC_SHL:
	case TILEGX_OPC_SHRU:
	case TILEGX_OPC_SHRS:
	case TILEGX_OPC_CMPLTU:
	case TILEGX_OPC_CMPLTS:
	case TILEGX_OPC_CMOVEQZ:
	case TILEGX_OPC_CMOVNEZ:
		inst_buf[inst_buf_index].input_registers = (1L << op1) | (1L << op2);
		inst_buf[inst_buf_index].output_registers = 1L << op0;
		break;
	case TILEGX_OPC_ADDLI:
	case TILEGX_OPC_XORI:
	case TILEGX_OPC_ORI:
	case TILEGX_OPC_SHLI:
	case TILEGX_OPC_SHRUI:
	case TILEGX_OPC_SHRSI:
	case TILEGX_OPC_SHL16INSLI:
	case TILEGX_OPC_CMPLTUI:
	case TILEGX_OPC_CMPLTSI:
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