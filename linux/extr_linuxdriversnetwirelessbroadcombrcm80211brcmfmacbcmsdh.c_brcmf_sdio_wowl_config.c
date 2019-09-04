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
struct brcmf_sdio_dev {int wowl_enabled; } ;
struct TYPE_2__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 

void brcmf_sdio_wowl_config(struct device *dev, bool enabled)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;

	brcmf_dbg(SDIO, "Configuring WOWL, enabled=%d\n", enabled);
	sdiodev->wowl_enabled = enabled;
}