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
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  target_execute_cmd (struct se_cmd*) ; 

__attribute__((used)) static int tcm_loop_write_pending(struct se_cmd *se_cmd)
{
	/*
	 * Since Linux/SCSI has already sent down a struct scsi_cmnd
	 * sc->sc_data_direction of DMA_TO_DEVICE with struct scatterlist array
	 * memory, and memory has already been mapped to struct se_cmd->t_mem_list
	 * format with transport_generic_map_mem_to_cmd().
	 *
	 * We now tell TCM to add this WRITE CDB directly into the TCM storage
	 * object execution queue.
	 */
	target_execute_cmd(se_cmd);
	return 0;
}