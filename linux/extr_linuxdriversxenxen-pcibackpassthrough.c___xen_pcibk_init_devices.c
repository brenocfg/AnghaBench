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
struct xen_pcibk_device {struct passthrough_dev_data* pci_dev_data; } ;
struct passthrough_dev_data {int /*<<< orphan*/  dev_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct passthrough_dev_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __xen_pcibk_init_devices(struct xen_pcibk_device *pdev)
{
	struct passthrough_dev_data *dev_data;

	dev_data = kmalloc(sizeof(*dev_data), GFP_KERNEL);
	if (!dev_data)
		return -ENOMEM;

	mutex_init(&dev_data->lock);

	INIT_LIST_HEAD(&dev_data->dev_list);

	pdev->pci_dev_data = dev_data;

	return 0;
}