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
struct skl_module_res {int /*<<< orphan*/  is_pages; int /*<<< orphan*/  obs; int /*<<< orphan*/  ibs; int /*<<< orphan*/  cpc; } ;
struct skl_module_iface {TYPE_1__* inputs; } ;
struct skl_module_fmt {int /*<<< orphan*/  interleaving_style; int /*<<< orphan*/  ch_map; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  channels; } ;
struct skl_module_cfg {size_t res_idx; size_t fmt_idx; struct skl_module* module; } ;
struct skl_module {struct skl_module_iface* formats; struct skl_module_res* resources; } ;
struct skl_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  interleaving; int /*<<< orphan*/  channel_map; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  number_of_channels; } ;
struct skl_base_cfg {int /*<<< orphan*/  is_pages; int /*<<< orphan*/  obs; int /*<<< orphan*/  ibs; int /*<<< orphan*/  cpc; TYPE_2__ audio_fmt; } ;
struct TYPE_3__ {struct skl_module_fmt fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_set_base_module_format(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_base_cfg *base_cfg)
{
	struct skl_module *module = mconfig->module;
	struct skl_module_res *res = &module->resources[mconfig->res_idx];
	struct skl_module_iface *fmt = &module->formats[mconfig->fmt_idx];
	struct skl_module_fmt *format = &fmt->inputs[0].fmt;

	base_cfg->audio_fmt.number_of_channels = format->channels;

	base_cfg->audio_fmt.s_freq = format->s_freq;
	base_cfg->audio_fmt.bit_depth = format->bit_depth;
	base_cfg->audio_fmt.valid_bit_depth = format->valid_bit_depth;
	base_cfg->audio_fmt.ch_cfg = format->ch_cfg;
	base_cfg->audio_fmt.sample_type = format->sample_type;

	dev_dbg(skl->dev, "bit_depth=%x valid_bd=%x ch_config=%x\n",
			format->bit_depth, format->valid_bit_depth,
			format->ch_cfg);

	base_cfg->audio_fmt.channel_map = format->ch_map;

	base_cfg->audio_fmt.interleaving = format->interleaving_style;

	base_cfg->cpc = res->cpc;
	base_cfg->ibs = res->ibs;
	base_cfg->obs = res->obs;
	base_cfg->is_pages = res->is_pages;
}