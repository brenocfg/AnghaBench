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
struct pps_device {int /*<<< orphan*/  id; int /*<<< orphan*/  cdev; } ;
struct device {int /*<<< orphan*/  id; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 struct pps_device* dev_get_drvdata (struct pps_device*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pps_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_idr ; 
 int /*<<< orphan*/  pps_idr_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pps_device_destruct(struct device *dev)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	cdev_del(&pps->cdev);

	/* Now we can release the ID for re-use */
	pr_debug("deallocating pps%d\n", pps->id);
	mutex_lock(&pps_idr_lock);
	idr_remove(&pps_idr, pps->id);
	mutex_unlock(&pps_idr_lock);

	kfree(dev);
	kfree(pps);
}