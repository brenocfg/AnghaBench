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
struct dyna_pci10xx_private {int /*<<< orphan*/  mutex; } ;
struct comedi_device {struct dyna_pci10xx_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dyna_pci10xx_detach(struct comedi_device *dev)
{
	struct dyna_pci10xx_private *devpriv = dev->private;

	comedi_pci_detach(dev);
	if (devpriv)
		mutex_destroy(&devpriv->mutex);
}