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
struct jr3_pci_dev_private {int /*<<< orphan*/  timer; } ;
struct comedi_device {struct jr3_pci_dev_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jr3_pci_detach(struct comedi_device *dev)
{
	struct jr3_pci_dev_private *devpriv = dev->private;

	if (devpriv)
		del_timer_sync(&devpriv->timer);

	comedi_pci_detach(dev);
}