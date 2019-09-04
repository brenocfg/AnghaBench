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
struct urdev {struct ccw_device* cdev; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  reclen; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_info; } ;
struct ccw_device {int /*<<< orphan*/  dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccw_device_get_id (struct ccw_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct urdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct urdev *urdev_alloc(struct ccw_device *cdev)
{
	struct urdev *urd;

	urd = kzalloc(sizeof(struct urdev), GFP_KERNEL);
	if (!urd)
		return NULL;
	urd->reclen = cdev->id.driver_info;
	ccw_device_get_id(cdev, &urd->dev_id);
	mutex_init(&urd->io_mutex);
	init_waitqueue_head(&urd->wait);
	spin_lock_init(&urd->open_lock);
	refcount_set(&urd->ref_count,  1);
	urd->cdev = cdev;
	get_device(&cdev->dev);
	return urd;
}