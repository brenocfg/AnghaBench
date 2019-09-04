#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct isci_remote_device {TYPE_3__* isci_port; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* isci_host; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct device *scirdev_to_dev(struct isci_remote_device *idev)
{
	if (!idev || !idev->isci_port || !idev->isci_port->isci_host)
		return NULL;

	return &idev->isci_port->isci_host->pdev->dev;
}