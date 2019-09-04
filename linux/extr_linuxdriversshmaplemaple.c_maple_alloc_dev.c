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
struct TYPE_2__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * bus; } ;
struct maple_device {int port; int unit; int /*<<< orphan*/  maple_wait; TYPE_1__ dev; int /*<<< orphan*/  mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct maple_device*) ; 
 struct maple_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_allocq (struct maple_device*) ; 
 int /*<<< orphan*/  maple_bus ; 
 int /*<<< orphan*/  maple_bus_type ; 

__attribute__((used)) static struct maple_device *maple_alloc_dev(int port, int unit)
{
	struct maple_device *mdev;

	/* zero this out to avoid kobj subsystem
	* thinking it has already been registered */

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return NULL;

	mdev->port = port;
	mdev->unit = unit;

	mdev->mq = maple_allocq(mdev);

	if (!mdev->mq) {
		kfree(mdev);
		return NULL;
	}
	mdev->dev.bus = &maple_bus_type;
	mdev->dev.parent = &maple_bus;
	init_waitqueue_head(&mdev->maple_wait);
	return mdev;
}