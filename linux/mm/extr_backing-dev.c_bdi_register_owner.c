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
struct device {int /*<<< orphan*/  devt; } ;
struct backing_dev_info {struct device* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (struct device*) ; 
 int bdi_register (struct backing_dev_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 

int bdi_register_owner(struct backing_dev_info *bdi, struct device *owner)
{
	int rc;

	rc = bdi_register(bdi, "%u:%u", MAJOR(owner->devt), MINOR(owner->devt));
	if (rc)
		return rc;
	/* Leaking owner reference... */
	WARN_ON(bdi->owner);
	bdi->owner = owner;
	get_device(owner);
	return 0;
}