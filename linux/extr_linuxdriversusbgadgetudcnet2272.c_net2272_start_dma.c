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
struct net2272 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
net2272_start_dma(struct net2272 *dev)
{
	/* start platform's dma controller */
#ifdef CONFIG_USB_PCI
	switch (dev->dev_id) {
	case PCI_DEVICE_ID_RDK1:
		writeb((1 << CHANNEL_ENABLE) | (1 << CHANNEL_START),
			dev->rdk1.plx9054_base_addr + DMACSR0);
		break;
	}
#endif
}