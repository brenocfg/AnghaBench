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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void vortex_fix_latency(struct pci_dev *vortex)
{
	int rc;
	if (!(rc = pci_write_config_byte(vortex, 0x40, 0xff))) {
			dev_info(&vortex->dev, "vortex latency is 0xff\n");
	} else {
		dev_warn(&vortex->dev,
			 "could not set vortex latency: pci error 0x%x\n", rc);
	}
}