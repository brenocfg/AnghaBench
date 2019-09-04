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
struct pci_dev {int dummy; } ;
struct pch_thermal_device {TYPE_1__* ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* suspend ) (struct pch_thermal_device*) ;} ;

/* Variables and functions */
 struct pch_thermal_device* pci_get_drvdata (struct pci_dev*) ; 
 int stub1 (struct pch_thermal_device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int intel_pch_thermal_suspend(struct device *device)
{
	struct pci_dev *pdev = to_pci_dev(device);
	struct pch_thermal_device *ptd = pci_get_drvdata(pdev);

	return ptd->ops->suspend(ptd);
}