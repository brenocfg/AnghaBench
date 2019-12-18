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
struct TYPE_6__ {int mclk; int keep_running; int warm_up_over; int clk_stop_over; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union skl_clk_ctrl_ipc {TYPE_3__ mclk; TYPE_2__ sclk_fs; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct skl_dmactrl_sclkfs_cfg {int dummy; } ;
struct skl_dmactrl_mclk_cfg {int dummy; } ;
struct skl_dev {int dummy; } ;
struct skl_clk_rate_cfg_table {scalar_t__ config; union skl_clk_ctrl_ipc dma_ctl_ipc; } ;
struct nhlt_specific_cfg {int size; scalar_t__* caps; } ;
struct nhlt_fmt_cfg {struct nhlt_specific_cfg config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANSMITION_START ; 
 int /*<<< orphan*/  DMA_TRANSMITION_STOP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKL_DMA_I2S_LINK_INPUT_CLASS ; 
 scalar_t__ SKL_SCLK ; 
 scalar_t__ SKL_SCLK_FS ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__*,scalar_t__) ; 
 int skl_dsp_set_dma_control (struct skl_dev*,int*,int,int) ; 

__attribute__((used)) static int skl_send_clk_dma_control(struct skl_dev *skl,
				struct skl_clk_rate_cfg_table *rcfg,
				u32 vbus_id, u8 clk_type,
				bool enable)
{
	struct nhlt_specific_cfg *sp_cfg;
	u32 i2s_config_size, node_id = 0;
	struct nhlt_fmt_cfg *fmt_cfg;
	union skl_clk_ctrl_ipc *ipc;
	void *i2s_config = NULL;
	u8 *data, size;
	int ret;

	if (!rcfg)
		return -EIO;

	ipc = &rcfg->dma_ctl_ipc;
	fmt_cfg = (struct nhlt_fmt_cfg *)rcfg->config;
	sp_cfg = &fmt_cfg->config;

	if (clk_type == SKL_SCLK_FS) {
		ipc->sclk_fs.hdr.type =
			enable ? DMA_TRANSMITION_START : DMA_TRANSMITION_STOP;
		data = (u8 *)&ipc->sclk_fs;
		size = sizeof(struct skl_dmactrl_sclkfs_cfg);
	} else {
		/* 1 to enable mclk, 0 to enable sclk */
		if (clk_type == SKL_SCLK)
			ipc->mclk.mclk = 0;
		else
			ipc->mclk.mclk = 1;

		ipc->mclk.keep_running = enable;
		ipc->mclk.warm_up_over = enable;
		ipc->mclk.clk_stop_over = !enable;
		data = (u8 *)&ipc->mclk;
		size = sizeof(struct skl_dmactrl_mclk_cfg);
	}

	i2s_config_size = sp_cfg->size + size;
	i2s_config = kzalloc(i2s_config_size, GFP_KERNEL);
	if (!i2s_config)
		return -ENOMEM;

	/* copy blob */
	memcpy(i2s_config, sp_cfg->caps, sp_cfg->size);

	/* copy additional dma controls information */
	memcpy(i2s_config + sp_cfg->size, data, size);

	node_id = ((SKL_DMA_I2S_LINK_INPUT_CLASS << 8) | (vbus_id << 4));
	ret = skl_dsp_set_dma_control(skl, (u32 *)i2s_config,
					i2s_config_size, node_id);
	kfree(i2s_config);

	return ret;
}