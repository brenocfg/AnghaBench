#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pmu {TYPE_1__* dev; scalar_t__ attr_update; scalar_t__ nr_addr_filters; int /*<<< orphan*/  name; int /*<<< orphan*/  attr_groups; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_nr_addr_filters ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct pmu*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_bus ; 
 int /*<<< orphan*/  pmu_dev_release ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int sysfs_update_groups (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int pmu_dev_alloc(struct pmu *pmu)
{
	int ret = -ENOMEM;

	pmu->dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!pmu->dev)
		goto out;

	pmu->dev->groups = pmu->attr_groups;
	device_initialize(pmu->dev);
	ret = dev_set_name(pmu->dev, "%s", pmu->name);
	if (ret)
		goto free_dev;

	dev_set_drvdata(pmu->dev, pmu);
	pmu->dev->bus = &pmu_bus;
	pmu->dev->release = pmu_dev_release;
	ret = device_add(pmu->dev);
	if (ret)
		goto free_dev;

	/* For PMUs with address filters, throw in an extra attribute: */
	if (pmu->nr_addr_filters)
		ret = device_create_file(pmu->dev, &dev_attr_nr_addr_filters);

	if (ret)
		goto del_dev;

	if (pmu->attr_update)
		ret = sysfs_update_groups(&pmu->dev->kobj, pmu->attr_update);

	if (ret)
		goto del_dev;

out:
	return ret;

del_dev:
	device_del(pmu->dev);

free_dev:
	put_device(pmu->dev);
	goto out;
}