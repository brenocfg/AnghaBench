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
struct pci_dev {int is_hotplug_bridge; } ;

/* Variables and functions */

__attribute__((used)) static void quirk_hotplug_bridge(struct pci_dev *dev)
{
	dev->is_hotplug_bridge = 1;
}