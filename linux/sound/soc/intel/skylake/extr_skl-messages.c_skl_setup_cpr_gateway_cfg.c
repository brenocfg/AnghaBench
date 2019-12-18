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
typedef  int u32 ;
struct skl_module_res {int dma_buffer_size; int ibs; int obs; } ;
struct skl_module_cfg {int res_idx; int hw_conn_type; int dma_buffer_size; int /*<<< orphan*/  dev_type; TYPE_1__* module; } ;
struct skl_dev {int /*<<< orphan*/  dev; scalar_t__ nr_modules; } ;
struct TYPE_4__ {scalar_t__ node_id; int dma_buffer_size; scalar_t__ config_length; } ;
struct skl_cpr_cfg {TYPE_2__ gtw_cfg; scalar_t__ cpr_feature_mask; } ;
struct TYPE_3__ {struct skl_module_res* resources; } ;

/* Variables and functions */
#define  SKL_CONN_SINK 129 
#define  SKL_CONN_SOURCE 128 
 int /*<<< orphan*/  SKL_DEVICE_HDAHOST ; 
 scalar_t__ SKL_NON_GATEWAY_CPR_NODE_ID ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  skl_copy_copier_caps (struct skl_module_cfg*,struct skl_cpr_cfg*) ; 
 scalar_t__ skl_get_node_id (struct skl_dev*,struct skl_module_cfg*) ; 

__attribute__((used)) static void skl_setup_cpr_gateway_cfg(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_cpr_cfg *cpr_mconfig)
{
	u32 dma_io_buf;
	struct skl_module_res *res;
	int res_idx = mconfig->res_idx;

	cpr_mconfig->gtw_cfg.node_id = skl_get_node_id(skl, mconfig);

	if (cpr_mconfig->gtw_cfg.node_id == SKL_NON_GATEWAY_CPR_NODE_ID) {
		cpr_mconfig->cpr_feature_mask = 0;
		return;
	}

	if (skl->nr_modules) {
		res = &mconfig->module->resources[mconfig->res_idx];
		cpr_mconfig->gtw_cfg.dma_buffer_size = res->dma_buffer_size;
		goto skip_buf_size_calc;
	} else {
		res = &mconfig->module->resources[res_idx];
	}

	switch (mconfig->hw_conn_type) {
	case SKL_CONN_SOURCE:
		if (mconfig->dev_type == SKL_DEVICE_HDAHOST)
			dma_io_buf =  res->ibs;
		else
			dma_io_buf =  res->obs;
		break;

	case SKL_CONN_SINK:
		if (mconfig->dev_type == SKL_DEVICE_HDAHOST)
			dma_io_buf =  res->obs;
		else
			dma_io_buf =  res->ibs;
		break;

	default:
		dev_warn(skl->dev, "wrong connection type: %d\n",
				mconfig->hw_conn_type);
		return;
	}

	cpr_mconfig->gtw_cfg.dma_buffer_size =
				mconfig->dma_buffer_size * dma_io_buf;

	/* fallback to 2ms default value */
	if (!cpr_mconfig->gtw_cfg.dma_buffer_size) {
		if (mconfig->hw_conn_type == SKL_CONN_SOURCE)
			cpr_mconfig->gtw_cfg.dma_buffer_size = 2 * res->obs;
		else
			cpr_mconfig->gtw_cfg.dma_buffer_size = 2 * res->ibs;
	}

skip_buf_size_calc:
	cpr_mconfig->cpr_feature_mask = 0;
	cpr_mconfig->gtw_cfg.config_length  = 0;

	skl_copy_copier_caps(mconfig, cpr_mconfig);
}