#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int time_slot_index; int i2s_instance; } ;
union skl_ssp_dma_node {int val; TYPE_2__ dma_node; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int vindex; void* dma_type; } ;
union skl_connector_node_id {int val; TYPE_3__ node; int /*<<< orphan*/  member_0; } ;
typedef  int u32 ;
struct skl_pipe_params {int host_dma_id; int link_dma_id; } ;
struct skl_module_cfg {int dev_type; int vbus_id; int time_slot; int /*<<< orphan*/  hw_conn_type; TYPE_1__* pipe; } ;
struct skl_dev {int dummy; } ;
struct TYPE_4__ {struct skl_pipe_params* p_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_CONN_SOURCE ; 
#define  SKL_DEVICE_BT 132 
#define  SKL_DEVICE_DMIC 131 
#define  SKL_DEVICE_HDAHOST 130 
#define  SKL_DEVICE_HDALINK 129 
#define  SKL_DEVICE_I2S 128 
 void* SKL_DMA_DMIC_LINK_INPUT_CLASS ; 
 void* SKL_DMA_HDA_HOST_INPUT_CLASS ; 
 void* SKL_DMA_HDA_HOST_OUTPUT_CLASS ; 
 void* SKL_DMA_HDA_LINK_INPUT_CLASS ; 
 void* SKL_DMA_HDA_LINK_OUTPUT_CLASS ; 
 void* SKL_DMA_I2S_LINK_INPUT_CLASS ; 
 void* SKL_DMA_I2S_LINK_OUTPUT_CLASS ; 

__attribute__((used)) static u32 skl_get_node_id(struct skl_dev *skl,
			struct skl_module_cfg *mconfig)
{
	union skl_connector_node_id node_id = {0};
	union skl_ssp_dma_node ssp_node  = {0};
	struct skl_pipe_params *params = mconfig->pipe->p_params;

	switch (mconfig->dev_type) {
	case SKL_DEVICE_BT:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_I2S_LINK_OUTPUT_CLASS :
			SKL_DMA_I2S_LINK_INPUT_CLASS;
		node_id.node.vindex = params->host_dma_id +
					(mconfig->vbus_id << 3);
		break;

	case SKL_DEVICE_I2S:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_I2S_LINK_OUTPUT_CLASS :
			SKL_DMA_I2S_LINK_INPUT_CLASS;
		ssp_node.dma_node.time_slot_index = mconfig->time_slot;
		ssp_node.dma_node.i2s_instance = mconfig->vbus_id;
		node_id.node.vindex = ssp_node.val;
		break;

	case SKL_DEVICE_DMIC:
		node_id.node.dma_type = SKL_DMA_DMIC_LINK_INPUT_CLASS;
		node_id.node.vindex = mconfig->vbus_id +
					 (mconfig->time_slot);
		break;

	case SKL_DEVICE_HDALINK:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_HDA_LINK_OUTPUT_CLASS :
			SKL_DMA_HDA_LINK_INPUT_CLASS;
		node_id.node.vindex = params->link_dma_id;
		break;

	case SKL_DEVICE_HDAHOST:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_HDA_HOST_OUTPUT_CLASS :
			SKL_DMA_HDA_HOST_INPUT_CLASS;
		node_id.node.vindex = params->host_dma_id;
		break;

	default:
		node_id.val = 0xFFFFFFFF;
		break;
	}

	return node_id.val;
}