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
struct pcie_device {int /*<<< orphan*/  irq; TYPE_1__* port; } ;
struct device {int dummy; } ;
struct aer_rpc {int isr; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 struct aer_rpc* aer_alloc_rpc (struct pcie_device*) ; 
 int /*<<< orphan*/  aer_enable_rootport (struct aer_rpc*) ; 
 int /*<<< orphan*/  aer_irq ; 
 int /*<<< orphan*/  aer_remove (struct pcie_device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,struct device*,char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcie_device*) ; 

__attribute__((used)) static int aer_probe(struct pcie_device *dev)
{
	int status;
	struct aer_rpc *rpc;
	struct device *device = &dev->port->dev;

	/* Alloc rpc data structure */
	rpc = aer_alloc_rpc(dev);
	if (!rpc) {
		dev_printk(KERN_DEBUG, device, "alloc AER rpc failed\n");
		aer_remove(dev);
		return -ENOMEM;
	}

	/* Request IRQ ISR */
	status = request_irq(dev->irq, aer_irq, IRQF_SHARED, "aerdrv", dev);
	if (status) {
		dev_printk(KERN_DEBUG, device, "request AER IRQ %d failed\n",
			   dev->irq);
		aer_remove(dev);
		return status;
	}

	rpc->isr = 1;

	aer_enable_rootport(rpc);
	dev_info(device, "AER enabled with IRQ %d\n", dev->irq);
	return 0;
}