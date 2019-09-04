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
struct mf6x4_private {scalar_t__ bar2_mem; scalar_t__ bar0_mem; } ;
struct comedi_device {struct mf6x4_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void mf6x4_detach(struct comedi_device *dev)
{
	struct mf6x4_private *devpriv = dev->private;

	if (devpriv) {
		if (devpriv->bar0_mem)
			iounmap(devpriv->bar0_mem);
		if (devpriv->bar2_mem)
			iounmap(devpriv->bar2_mem);
	}
	comedi_pci_detach(dev);
}