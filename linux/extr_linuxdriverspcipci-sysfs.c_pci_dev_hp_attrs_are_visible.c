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
typedef  int /*<<< orphan*/  umode_t ;
struct pci_dev {scalar_t__ is_virtfn; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 struct device* kobj_to_dev (struct kobject*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static umode_t pci_dev_hp_attrs_are_visible(struct kobject *kobj,
					    struct attribute *a, int n)
{
	struct device *dev = kobj_to_dev(kobj);
	struct pci_dev *pdev = to_pci_dev(dev);

	if (pdev->is_virtfn)
		return 0;

	return a->mode;
}