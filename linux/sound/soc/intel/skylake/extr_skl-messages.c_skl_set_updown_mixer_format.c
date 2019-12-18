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
struct skl_up_down_mixer_cfg {int /*<<< orphan*/  ch_map; int /*<<< orphan*/  out_ch_cfg; } ;
struct skl_module_iface {TYPE_1__* outputs; } ;
struct skl_module_fmt {int /*<<< orphan*/  ch_map; int /*<<< orphan*/  ch_cfg; } ;
struct skl_module_cfg {size_t fmt_idx; struct skl_module* module; } ;
struct skl_module {struct skl_module_iface* formats; } ;
struct skl_dev {int dummy; } ;
struct skl_base_cfg {int dummy; } ;
struct TYPE_2__ {struct skl_module_fmt fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_set_base_module_format (struct skl_dev*,struct skl_module_cfg*,struct skl_base_cfg*) ; 

__attribute__((used)) static void skl_set_updown_mixer_format(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_up_down_mixer_cfg *mixer_mconfig)
{
	struct skl_module *module = mconfig->module;
	struct skl_module_iface *iface = &module->formats[mconfig->fmt_idx];
	struct skl_module_fmt *fmt = &iface->outputs[0].fmt;

	skl_set_base_module_format(skl,	mconfig,
		(struct skl_base_cfg *)mixer_mconfig);
	mixer_mconfig->out_ch_cfg = fmt->ch_cfg;
	mixer_mconfig->ch_map = fmt->ch_map;
}