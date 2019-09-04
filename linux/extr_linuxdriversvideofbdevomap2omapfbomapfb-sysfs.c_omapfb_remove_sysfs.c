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
struct omapfb2_device {int num_fbs; TYPE_1__** fbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * omapfb_attrs ; 

void omapfb_remove_sysfs(struct omapfb2_device *fbdev)
{
	int i, t;

	DBG("remove sysfs for fbs\n");
	for (i = 0; i < fbdev->num_fbs; i++) {
		for (t = 0; t < ARRAY_SIZE(omapfb_attrs); t++)
			device_remove_file(fbdev->fbs[i]->dev,
					&omapfb_attrs[t]);
	}
}