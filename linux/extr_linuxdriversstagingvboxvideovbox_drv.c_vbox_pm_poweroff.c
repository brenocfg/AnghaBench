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
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_device* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 int vbox_drm_freeze (struct drm_device*) ; 

__attribute__((used)) static int vbox_pm_poweroff(struct device *dev)
{
	struct drm_device *ddev = pci_get_drvdata(to_pci_dev(dev));

	return vbox_drm_freeze(ddev);
}