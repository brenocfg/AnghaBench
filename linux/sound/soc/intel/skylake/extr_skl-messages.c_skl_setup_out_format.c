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
typedef  scalar_t__ u8 ;
struct skl_module_iface {TYPE_1__* outputs; } ;
struct skl_module_fmt {int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  interleaving_style; int /*<<< orphan*/  ch_map; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; scalar_t__ channels; } ;
struct skl_module_cfg {size_t fmt_idx; struct skl_module* module; } ;
struct skl_module {struct skl_module_iface* formats; } ;
struct skl_dev {int /*<<< orphan*/  dev; } ;
struct skl_audio_data_format {scalar_t__ number_of_channels; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  interleaving; int /*<<< orphan*/  channel_map; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; } ;
struct TYPE_2__ {struct skl_module_fmt fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_setup_out_format(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_audio_data_format *out_fmt)
{
	struct skl_module *module = mconfig->module;
	struct skl_module_iface *fmt = &module->formats[mconfig->fmt_idx];
	struct skl_module_fmt *format = &fmt->outputs[0].fmt;

	out_fmt->number_of_channels = (u8)format->channels;
	out_fmt->s_freq = format->s_freq;
	out_fmt->bit_depth = format->bit_depth;
	out_fmt->valid_bit_depth = format->valid_bit_depth;
	out_fmt->ch_cfg = format->ch_cfg;

	out_fmt->channel_map = format->ch_map;
	out_fmt->interleaving = format->interleaving_style;
	out_fmt->sample_type = format->sample_type;

	dev_dbg(skl->dev, "copier out format chan=%d fre=%d bitdepth=%d\n",
		out_fmt->number_of_channels, format->s_freq, format->bit_depth);
}