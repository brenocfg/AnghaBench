#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct skl_pipe_params {scalar_t__ stream; int s_freq; int ch; int /*<<< orphan*/  s_fmt; } ;
struct skl_module_res {int ibs; int obs; } ;
struct skl_module_fmt {int s_freq; int channels; int valid_bit_depth; int bit_depth; } ;
struct skl_module_cfg {TYPE_6__* module; TYPE_2__* mod_cfg; int /*<<< orphan*/  res_idx; int /*<<< orphan*/  fmt_idx; TYPE_1__* pipe; } ;
struct skl_dev {scalar_t__ nr_modules; } ;
struct device {int dummy; } ;
struct TYPE_12__ {TYPE_5__* formats; struct skl_module_res* resources; } ;
struct TYPE_11__ {TYPE_4__* outputs; TYPE_3__* inputs; } ;
struct TYPE_10__ {struct skl_module_fmt fmt; } ;
struct TYPE_9__ {struct skl_module_fmt fmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  res_idx; int /*<<< orphan*/  fmt_idx; } ;
struct TYPE_7__ {size_t cur_config_idx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DEPTH_16BIT 130 
#define  SKL_DEPTH_24BIT 129 
#define  SKL_DEPTH_32BIT 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct skl_dev* get_skl_ctx (struct device*) ; 
 int skl_get_bit_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_tplg_fill_dma_id (struct skl_module_cfg*,struct skl_pipe_params*) ; 

int skl_tplg_update_pipe_params(struct device *dev,
			struct skl_module_cfg *mconfig,
			struct skl_pipe_params *params)
{
	struct skl_module_res *res = &mconfig->module->resources[0];
	struct skl_dev *skl = get_skl_ctx(dev);
	struct skl_module_fmt *format = NULL;
	u8 cfg_idx = mconfig->pipe->cur_config_idx;

	skl_tplg_fill_dma_id(mconfig, params);
	mconfig->fmt_idx = mconfig->mod_cfg[cfg_idx].fmt_idx;
	mconfig->res_idx = mconfig->mod_cfg[cfg_idx].res_idx;

	if (skl->nr_modules)
		return 0;

	if (params->stream == SNDRV_PCM_STREAM_PLAYBACK)
		format = &mconfig->module->formats[0].inputs[0].fmt;
	else
		format = &mconfig->module->formats[0].outputs[0].fmt;

	/* set the hw_params */
	format->s_freq = params->s_freq;
	format->channels = params->ch;
	format->valid_bit_depth = skl_get_bit_depth(params->s_fmt);

	/*
	 * 16 bit is 16 bit container whereas 24 bit is in 32 bit
	 * container so update bit depth accordingly
	 */
	switch (format->valid_bit_depth) {
	case SKL_DEPTH_16BIT:
		format->bit_depth = format->valid_bit_depth;
		break;

	case SKL_DEPTH_24BIT:
	case SKL_DEPTH_32BIT:
		format->bit_depth = SKL_DEPTH_32BIT;
		break;

	default:
		dev_err(dev, "Invalid bit depth %x for pipe\n",
				format->valid_bit_depth);
		return -EINVAL;
	}

	if (params->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		res->ibs = (format->s_freq / 1000) *
				(format->channels) *
				(format->bit_depth >> 3);
	} else {
		res->obs = (format->s_freq / 1000) *
				(format->channels) *
				(format->bit_depth >> 3);
	}

	return 0;
}