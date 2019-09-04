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
struct workqueue_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct omapfb_display_data {int auto_update_work_enabled; TYPE_1__ auto_update_work; } ;
struct omapfb2_device {struct workqueue_struct* auto_update_wq; int /*<<< orphan*/  dev; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct omapfb_display_data* get_display_data (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_auto_update_work (int /*<<< orphan*/ *) ; 

void omapfb_start_auto_update(struct omapfb2_device *fbdev,
		struct omap_dss_device *display)
{
	struct omapfb_display_data *d;

	if (fbdev->auto_update_wq == NULL) {
		struct workqueue_struct *wq;

		wq = create_singlethread_workqueue("omapfb_auto_update");

		if (wq == NULL) {
			dev_err(fbdev->dev, "Failed to create workqueue for "
					"auto-update\n");
			return;
		}

		fbdev->auto_update_wq = wq;
	}

	d = get_display_data(fbdev, display);

	INIT_DELAYED_WORK(&d->auto_update_work, omapfb_auto_update_work);

	d->auto_update_work_enabled = true;

	omapfb_auto_update_work(&d->auto_update_work.work);
}