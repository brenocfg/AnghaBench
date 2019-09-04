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
struct gbphy_driver {int /*<<< orphan*/  (* remove ) (struct gbphy_device*) ;} ;
struct gbphy_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct gbphy_device*) ; 
 struct gbphy_device* to_gbphy_dev (struct device*) ; 
 struct gbphy_driver* to_gbphy_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbphy_dev_remove(struct device *dev)
{
	struct gbphy_driver *gbphy_drv = to_gbphy_driver(dev->driver);
	struct gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	gbphy_drv->remove(gbphy_dev);

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);
	pm_runtime_dont_use_autosuspend(dev);

	return 0;
}