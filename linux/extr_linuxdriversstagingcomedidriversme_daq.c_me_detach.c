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
struct me_private_data {scalar_t__ plx_regbase; } ;
struct comedi_device {scalar_t__ mmio; struct me_private_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  me_reset (struct comedi_device*) ; 

__attribute__((used)) static void me_detach(struct comedi_device *dev)
{
	struct me_private_data *devpriv = dev->private;

	if (devpriv) {
		if (dev->mmio)
			me_reset(dev);
		if (devpriv->plx_regbase)
			iounmap(devpriv->plx_regbase);
	}
	comedi_pci_detach(dev);
}