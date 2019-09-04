#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tilegx_pipeline ;
typedef  int /*<<< orphan*/  tilegx_mnemonic ;
struct Format {scalar_t__* pipe; } ;
typedef  int sljit_s32 ;
struct TYPE_4__ {unsigned long input_registers; unsigned long output_registers; scalar_t__ pipe; TYPE_1__* opcode; } ;
struct TYPE_3__ {scalar_t__ can_bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TILEGX_OPC_FNOP ; 
 int /*<<< orphan*/  TILEGX_OPC_NOP ; 
 scalar_t__ TILEGX_PIPELINE_Y0 ; 
 scalar_t__ TILEGX_PIPELINE_Y1 ; 
 scalar_t__ TILEGX_PIPELINE_Y2 ; 
 struct Format* compute_format () ; 
 int /*<<< orphan*/  insert_nop (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* inst_buf ; 
 int inst_buf_index ; 
 int /*<<< orphan*/  tilegx_is_x_pipeline (scalar_t__) ; 

sljit_s32 assign_pipes()
{
	unsigned long output_registers = 0;
	unsigned int i = 0;

	if (inst_buf_index == 1) {
		tilegx_mnemonic opc = inst_buf[0].opcode->can_bundle
					? TILEGX_OPC_FNOP : TILEGX_OPC_NOP;
		insert_nop(opc, __LINE__);
	}

	const struct Format* match = compute_format();

	if (match == NULL)
		return -1;

	for (i = 0; i < inst_buf_index; i++) {

		if ((i > 0) && ((inst_buf[i].input_registers & output_registers) != 0))
			return -1;

		if ((i > 0) && ((inst_buf[i].output_registers & output_registers) != 0))
			return -1;

		/* Don't include Rzero in the match set, to avoid triggering
		   needlessly on 'prefetch' instrs. */

		output_registers |= inst_buf[i].output_registers & 0xFFFFFFFFFFFFFFL;

		inst_buf[i].pipe = match->pipe[i];
	}

	/* If only 2 instrs, and in Y-mode, insert a nop. */
	if (inst_buf_index == 2 && !tilegx_is_x_pipeline(match->pipe[0])) {
		insert_nop(TILEGX_OPC_FNOP, __LINE__);

		/* Select the yet unassigned pipe. */
		tilegx_pipeline pipe = (tilegx_pipeline)(((TILEGX_PIPELINE_Y0
					+ TILEGX_PIPELINE_Y1 + TILEGX_PIPELINE_Y2)
					- (inst_buf[1].pipe + inst_buf[2].pipe)));

		inst_buf[0].pipe = pipe;
	}

	return 0;
}