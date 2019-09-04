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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct skl_dsp_ops {int (* init_fw ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_8__ {TYPE_5__* astate_cfg; } ;
struct skl {TYPE_2__ cfg; TYPE_3__* skl_sst; TYPE_1__* pci; int /*<<< orphan*/  debugfs; struct snd_soc_component* component; } ;
struct hdac_bus {scalar_t__ ppcap; } ;
struct TYPE_10__ {int /*<<< orphan*/  count; } ;
struct TYPE_9__ {int is_first_boot; int /*<<< orphan*/  update_d0i3c; int /*<<< orphan*/  (* clock_power_gating ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_miscbdcge ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EIO ; 
 struct skl* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct hdac_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_debugfs_init (struct skl*) ; 
 int /*<<< orphan*/  skl_dsp_enable_notification (TYPE_3__*,int) ; 
 int /*<<< orphan*/  skl_dsp_set_astate_cfg (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 struct skl_dsp_ops* skl_get_dsp_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_populate_modules (struct skl*) ; 
 int skl_tplg_init (struct snd_soc_component*,struct hdac_bus*) ; 
 int /*<<< orphan*/  skl_update_d0i3c ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int skl_platform_soc_probe(struct snd_soc_component *component)
{
	struct hdac_bus *bus = dev_get_drvdata(component->dev);
	struct skl *skl = bus_to_skl(bus);
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

		if (skl->skl_sst->is_first_boot == false) {
			dev_err(component->dev, "DSP reports first boot done!!!\n");
			return -EIO;
		}

		/*
		 * Disable dynamic clock and power gating during firmware
		 * and library download
		 */
		skl->skl_sst->enable_miscbdcge(component->dev, false);
		skl->skl_sst->clock_power_gating(component->dev, false);

		ret = ops->init_fw(component->dev, skl->skl_sst);
		skl->skl_sst->enable_miscbdcge(component->dev, true);
		skl->skl_sst->clock_power_gating(component->dev, true);
		if (ret < 0) {
			dev_err(component->dev, "Failed to boot first fw: %d\n", ret);
			return ret;
		}
		skl_populate_modules(skl);
		skl->skl_sst->update_d0i3c = skl_update_d0i3c;
		skl_dsp_enable_notification(skl->skl_sst, false);

		if (skl->cfg.astate_cfg != NULL) {
			skl_dsp_set_astate_cfg(skl->skl_sst,
					skl->cfg.astate_cfg->count,
					skl->cfg.astate_cfg);
		}
	}
	pm_runtime_mark_last_busy(component->dev);
	pm_runtime_put_autosuspend(component->dev);

	return 0;
}