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
struct platform_device {int dummy; } ;
struct cpcap_charger_ddata {int /*<<< orphan*/  detect_work; int /*<<< orphan*/  vbus_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int cpcap_charger_set_state (struct cpcap_charger_ddata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int omap_usb2_set_comparator (int /*<<< orphan*/ *) ; 
 struct cpcap_charger_ddata* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cpcap_charger_remove(struct platform_device *pdev)
{
	struct cpcap_charger_ddata *ddata = platform_get_drvdata(pdev);
	int error;

	atomic_set(&ddata->active, 0);
	error = omap_usb2_set_comparator(NULL);
	if (error)
		dev_warn(ddata->dev, "could not clear USB comparator: %i\n",
			 error);

	error = cpcap_charger_set_state(ddata, 0, 0, 0);
	if (error)
		dev_warn(ddata->dev, "could not clear charger: %i\n",
			 error);
	cancel_delayed_work_sync(&ddata->vbus_work);
	cancel_delayed_work_sync(&ddata->detect_work);

	return 0;
}