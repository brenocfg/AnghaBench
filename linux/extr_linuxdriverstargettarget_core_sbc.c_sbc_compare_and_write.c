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
struct TYPE_2__ {int block_size; } ;
struct se_device {int /*<<< orphan*/  caw_sem; TYPE_1__ dev_attrib; } ;
struct se_cmd {int data_length; int t_task_nolb; int /*<<< orphan*/ * transport_complete_callback; int /*<<< orphan*/  t_bidi_data_nents; int /*<<< orphan*/  t_bidi_data_sg; struct se_device* se_dev; struct sbc_ops* protocol_data; } ;
struct sbc_ops {scalar_t__ (* execute_rw ) (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 scalar_t__ TCM_NO_SENSE ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sense_reason_t
sbc_compare_and_write(struct se_cmd *cmd)
{
	struct sbc_ops *ops = cmd->protocol_data;
	struct se_device *dev = cmd->se_dev;
	sense_reason_t ret;
	int rc;
	/*
	 * Submit the READ first for COMPARE_AND_WRITE to perform the
	 * comparision using SGLs at cmd->t_bidi_data_sg..
	 */
	rc = down_interruptible(&dev->caw_sem);
	if (rc != 0) {
		cmd->transport_complete_callback = NULL;
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}
	/*
	 * Reset cmd->data_length to individual block_size in order to not
	 * confuse backend drivers that depend on this value matching the
	 * size of the I/O being submitted.
	 */
	cmd->data_length = cmd->t_task_nolb * dev->dev_attrib.block_size;

	ret = ops->execute_rw(cmd, cmd->t_bidi_data_sg, cmd->t_bidi_data_nents,
			      DMA_FROM_DEVICE);
	if (ret) {
		cmd->transport_complete_callback = NULL;
		up(&dev->caw_sem);
		return ret;
	}
	/*
	 * Unlock of dev->caw_sem to occur in compare_and_write_callback()
	 * upon MISCOMPARE, or in compare_and_write_done() upon completion
	 * of WRITE instance user-data.
	 */
	return TCM_NO_SENSE;
}