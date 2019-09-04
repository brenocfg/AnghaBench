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
struct pcifront_device {TYPE_1__* xdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct pcifront_device* pcifront_dev ; 
 int /*<<< orphan*/  pcifront_dev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcifront_disconnect(struct pcifront_device *pdev)
{
	spin_lock(&pcifront_dev_lock);

	if (pdev == pcifront_dev) {
		dev_info(&pdev->xdev->dev,
			 "Disconnecting PCI Frontend Buses\n");
		pcifront_dev = NULL;
	}

	spin_unlock(&pcifront_dev_lock);
}