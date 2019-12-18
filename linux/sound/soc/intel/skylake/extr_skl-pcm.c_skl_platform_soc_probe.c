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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct skl_dsp_ops {int (* init_fw ) (int /*<<< orphan*/ ,struct skl_dev*) ;} ;
struct TYPE_5__ {TYPE_3__* astate_cfg; } ;
struct skl_dev {TYPE_2__ cfg; int /*<<< orphan*/  update_d0i3c; int /*<<< orphan*/  (* clock_power_gating ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_miscbdcge ) (int /*<<< orphan*/ ,int) ;TYPE_1__* pci; int /*<<< orphan*/  debugfs; struct snd_soc_component* component; } ;
struct hdac_bus {scalar_t__ ppcap; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EIO ; 
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct hdac_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_debugfs_init (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_dsp_set_astate_cfg (struct skl_dev*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct skl_dsp_ops* skl_get_dsp_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_populate_modules (struct skl_dev*) ; 
 int skl_tplg_init (struct snd_soc_component*,struct hdac_bus*) ; 
 int /*<<< orphan*/  skl_update_d0i3c ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,struct skl_dev*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int skl_platform_soc_probe(struct snd_soc_component *component)
{
	struct hdac_bus *bus = dev_get_drvdata(component->dev);
	struct skl_dev *skl = bus_to_skl(bus);
	const struct skl_dsp_ops *ops;
	int ret;

	pm_runtime_get_sync(component->dev);
	if (bus->ppcap) {
		skl->component = component;

		/* init debugfs */
		skl->debugfs = skl_debugfs_init(skl);

		ret = skl_tplg_init(component, bus);
		if (ret < 0) {
			dev_err(component->dev, "Failed to init topology!\n");
			return ret;
		}

		/* load the firmwares, since all is set */
		ops = skl_get_dsp_ops(skl->pci->device);
		if (!ops)
			return -EIO;

		/*
		 * Disable dynamic clock and power gating during firmware
		 * and library download
		 */
		skl->enable_miscbdcge(component->dev, false);
		skl->clock_power_gating(component->dev, false);

		ret = ops->init_fw(component->dev, skl);
		skl->enable_miscbdcge(component->dev, true);
		skl->clock_power_gating(component->dev, true);
		if (ret < 0) {
			dev_err(component->dev, "Failed to boot first fw: %d\n", ret);
			return ret;
		}
		skl_populate_modules(skl);
		skl->update_d0i3c = skl_update_d0i3c;

		if (skl->cfg.astate_cfg != NULL) {
			skl_dsp_set_astate_cfg(skl,
					skl->cfg.astate_cfg->count,
					skl->cfg.astate_cfg);
		}
	}
	pm_runtime_mark_last_busy(component->dev);
	pm_runtime_put_autosuspend(component->dev);

	return 0;
}