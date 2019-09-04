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
struct TYPE_4__ {int /*<<< orphan*/ * platform_data; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct TYPE_5__ {TYPE_3__* platdev; } ;

/* Variables and functions */
 int N_SUBDEVS ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_3__*) ; 
 TYPE_2__* viafb_subdevs ; 

__attribute__((used)) static void via_teardown_subdevs(void)
{
	int i;

	for (i = 0; i < N_SUBDEVS; i++)
		if (viafb_subdevs[i].platdev) {
			viafb_subdevs[i].platdev->dev.platform_data = NULL;
			platform_device_unregister(viafb_subdevs[i].platdev);
		}
}