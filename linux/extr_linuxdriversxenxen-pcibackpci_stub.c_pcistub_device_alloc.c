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
struct pcistub_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct pcistub_device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct pcistub_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pcistub_device *pcistub_device_alloc(struct pci_dev *dev)
{
	struct pcistub_device *psdev;

	dev_dbg(&dev->dev, "pcistub_device_alloc\n");

	psdev = kzalloc(sizeof(*psdev), GFP_KERNEL);
	if (!psdev)
		return NULL;

	psdev->dev = pci_dev_get(dev);
	if (!psdev->dev) {
		kfree(psdev);
		return NULL;
	}

	kref_init(&psdev->kref);
	spin_lock_init(&psdev->lock);

	return psdev;
}