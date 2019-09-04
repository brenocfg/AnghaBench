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
struct device {int dummy; } ;
struct brcmf_pciedev_info {int wowl_enabled; } ;
struct brcmf_pciedev {struct brcmf_pciedev_info* devinfo; } ;
struct TYPE_2__ {struct brcmf_pciedev* pcie; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void brcmf_pcie_wowl_config(struct device *dev, bool enabled)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_pciedev *buspub = bus_if->bus_priv.pcie;
	struct brcmf_pciedev_info *devinfo = buspub->devinfo;

	brcmf_dbg(PCIE, "Configuring WOWL, enabled=%d\n", enabled);
	devinfo->wowl_enabled = enabled;
}