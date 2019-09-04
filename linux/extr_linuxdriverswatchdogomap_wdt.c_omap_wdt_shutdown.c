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
struct omap_wdt_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ omap_wdt_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_wdt_disable (struct omap_wdt_dev*) ; 
 struct omap_wdt_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_wdt_shutdown(struct platform_device *pdev)
{
	struct omap_wdt_dev *wdev = platform_get_drvdata(pdev);

	mutex_lock(&wdev->lock);
	if (wdev->omap_wdt_users) {
		omap_wdt_disable(wdev);
		pm_runtime_put_sync(wdev->dev);
	}
	mutex_unlock(&wdev->lock);
}