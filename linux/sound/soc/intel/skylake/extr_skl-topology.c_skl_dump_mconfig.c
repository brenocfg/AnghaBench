#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct skl_module_iface {TYPE_5__* outputs; TYPE_3__* inputs; } ;
struct skl_module_cfg {TYPE_1__* module; } ;
struct skl_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  channels; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  channels; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct TYPE_6__ {struct skl_module_iface* formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void skl_dump_mconfig(struct skl_dev *skl, struct skl_module_cfg *mcfg)
{
	struct skl_module_iface *iface = &mcfg->module->formats[0];

	dev_dbg(skl->dev, "Dumping config\n");
	dev_dbg(skl->dev, "Input Format:\n");
	dev_dbg(skl->dev, "channels = %d\n", iface->inputs[0].fmt.channels);
	dev_dbg(skl->dev, "s_freq = %d\n", iface->inputs[0].fmt.s_freq);
	dev_dbg(skl->dev, "ch_cfg = %d\n", iface->inputs[0].fmt.ch_cfg);
	dev_dbg(skl->dev, "valid bit depth = %d\n",
				iface->inputs[0].fmt.valid_bit_depth);
	dev_dbg(skl->dev, "Output Format:\n");
	dev_dbg(skl->dev, "channels = %d\n", iface->outputs[0].fmt.channels);
	dev_dbg(skl->dev, "s_freq = %d\n", iface->outputs[0].fmt.s_freq);
	dev_dbg(skl->dev, "valid bit depth = %d\n",
				iface->outputs[0].fmt.valid_bit_depth);
	dev_dbg(skl->dev, "ch_cfg = %d\n", iface->outputs[0].fmt.ch_cfg);
}