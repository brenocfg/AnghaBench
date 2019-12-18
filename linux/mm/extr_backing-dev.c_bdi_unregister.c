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
struct backing_dev_info {int /*<<< orphan*/ * owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdi_debug_unregister (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_remove_from_list (struct backing_dev_info*) ; 
 int /*<<< orphan*/  cgwb_bdi_unregister (struct backing_dev_info*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_shutdown (int /*<<< orphan*/ *) ; 

void bdi_unregister(struct backing_dev_info *bdi)
{
	/* make sure nobody finds us on the bdi_list anymore */
	bdi_remove_from_list(bdi);
	wb_shutdown(&bdi->wb);
	cgwb_bdi_unregister(bdi);

	if (bdi->dev) {
		bdi_debug_unregister(bdi);
		device_unregister(bdi->dev);
		bdi->dev = NULL;
	}

	if (bdi->owner) {
		put_device(bdi->owner);
		bdi->owner = NULL;
	}
}