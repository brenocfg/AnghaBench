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
struct dwc_otg_hcd {TYPE_3__* otg_dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* platformdev; } ;
struct TYPE_6__ {TYPE_2__ os_dep; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct device *dwc_otg_hcd_to_dev(struct dwc_otg_hcd *hcd)
{
	return &hcd->otg_dev->os_dep.platformdev->dev;
}