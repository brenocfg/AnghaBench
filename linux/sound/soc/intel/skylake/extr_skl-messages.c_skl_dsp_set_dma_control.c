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
struct skl_ipc_large_config_msg {scalar_t__ param_data_size; int /*<<< orphan*/  large_param_id; int /*<<< orphan*/  member_0; } ;
struct skl_dma_control {int /*<<< orphan*/  config_data; int /*<<< orphan*/  config_length; int /*<<< orphan*/  node_id; } ;
struct skl_dev {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL_ID ; 
 int /*<<< orphan*/  DMA_I2S_BLOB_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct skl_dma_control*) ; 
 struct skl_dma_control* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int skl_ipc_set_large_config (int /*<<< orphan*/ *,struct skl_ipc_large_config_msg*,int /*<<< orphan*/ *) ; 

int skl_dsp_set_dma_control(struct skl_dev *skl, u32 *caps,
				u32 caps_size, u32 node_id)
{
	struct skl_dma_control *dma_ctrl;
	struct skl_ipc_large_config_msg msg = {0};
	int err = 0;


	/*
	 * if blob size zero, then return
	 */
	if (caps_size == 0)
		return 0;

	msg.large_param_id = DMA_CONTROL_ID;
	msg.param_data_size = sizeof(struct skl_dma_control) + caps_size;

	dma_ctrl = kzalloc(msg.param_data_size, GFP_KERNEL);
	if (dma_ctrl == NULL)
		return -ENOMEM;

	dma_ctrl->node_id = node_id;

	/*
	 * NHLT blob may contain additional configs along with i2s blob.
	 * firmware expects only the i2s blob size as the config_length.
	 * So fix to i2s blob size.
	 * size in dwords.
	 */
	dma_ctrl->config_length = DMA_I2S_BLOB_SIZE;

	memcpy(dma_ctrl->config_data, caps, caps_size);

	err = skl_ipc_set_large_config(&skl->ipc, &msg, (u32 *)dma_ctrl);

	kfree(dma_ctrl);
	return err;
}