#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct hdac_bus {int /*<<< orphan*/  spbcap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_REG_SPB_SPBFCCTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_hdac_updatel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void snd_hdac_ext_stream_spbcap_enable(struct hdac_bus *bus,
				 bool enable, int index)
{
	u32 mask = 0;

	if (!bus->spbcap) {
		dev_err(bus->dev, "Address of SPB capability is NULL\n");
		return;
	}

	mask |= (1 << index);

	if (enable)
		snd_hdac_updatel(bus->spbcap, AZX_REG_SPB_SPBFCCTL, mask, mask);
	else
		snd_hdac_updatel(bus->spbcap, AZX_REG_SPB_SPBFCCTL, mask, 0);
}