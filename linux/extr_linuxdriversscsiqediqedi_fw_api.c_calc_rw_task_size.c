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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_sgl_task_params {int /*<<< orphan*/  total_buffer_size; } ;
struct scsi_dif_task_params {int /*<<< orphan*/  dif_on_network; } ;
struct iscsi_task_params {int /*<<< orphan*/  rx_io_size; int /*<<< orphan*/  tx_io_size; } ;
typedef  enum iscsi_task_type { ____Placeholder_iscsi_task_type } iscsi_task_type ;

/* Variables and functions */
 int ISCSI_TASK_TYPE_INITIATOR_WRITE ; 
 int ISCSI_TASK_TYPE_TARGET_READ ; 

__attribute__((used)) static u32 calc_rw_task_size(struct iscsi_task_params *task_params,
			     enum iscsi_task_type task_type,
			     struct scsi_sgl_task_params *sgl_task_params,
			     struct scsi_dif_task_params *dif_task_params)
{
	u32 io_size;

	if (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE ||
	    task_type == ISCSI_TASK_TYPE_TARGET_READ)
		io_size = task_params->tx_io_size;
	else
		io_size = task_params->rx_io_size;

	if (!io_size)
		return 0;

	if (!dif_task_params)
		return io_size;

	return !dif_task_params->dif_on_network ?
	       io_size : sgl_task_params->total_buffer_size;
}