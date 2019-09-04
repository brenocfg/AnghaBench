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
struct visor_device {int /*<<< orphan*/  visorchannel; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  debugfs_bus_info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct visor_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct visor_device*) ; 
 int /*<<< orphan*/  visorchannel_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void visorbus_release_busdevice(struct device *xdev)
{
	struct visor_device *dev = dev_get_drvdata(xdev);

	debugfs_remove(dev->debugfs_bus_info);
	debugfs_remove_recursive(dev->debugfs_dir);
	visorchannel_destroy(dev->visorchannel);
	kfree(dev);
}