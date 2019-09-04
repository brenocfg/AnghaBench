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
struct pci_dev {int subsystem_device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int pci_inteli960ni_init(struct pci_dev *dev)
{
	u32 oldval;

	if (!(dev->subsystem_device & 0x1000))
		return -ENODEV;

	/* is firmware started? */
	pci_read_config_dword(dev, 0x44, &oldval);
	if (oldval == 0x00001000L) { /* RESET value */
		dev_dbg(&dev->dev, "Local i960 firmware missing\n");
		return -ENODEV;
	}
	return 0;
}