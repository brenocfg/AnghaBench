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
struct device {int dummy; } ;
struct rproc {int /*<<< orphan*/  node; scalar_t__ auto_boot; int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_create_debug_dir (struct rproc*) ; 
 int /*<<< orphan*/  rproc_list ; 
 int /*<<< orphan*/  rproc_list_mutex ; 
 int rproc_trigger_auto_boot (struct rproc*) ; 

int rproc_add(struct rproc *rproc)
{
	struct device *dev = &rproc->dev;
	int ret;

	ret = device_add(dev);
	if (ret < 0)
		return ret;

	dev_info(dev, "%s is available\n", rproc->name);

	/* create debugfs entries */
	rproc_create_debug_dir(rproc);

	/* if rproc is marked always-on, request it to boot */
	if (rproc->auto_boot) {
		ret = rproc_trigger_auto_boot(rproc);
		if (ret < 0)
			return ret;
	}

	/* expose to rproc_get_by_phandle users */
	mutex_lock(&rproc_list_mutex);
	list_add(&rproc->node, &rproc_list);
	mutex_unlock(&rproc_list_mutex);

	return 0;
}