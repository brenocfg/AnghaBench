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
struct comedi_device {int minor; int /*<<< orphan*/  attach_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void comedi_device_init(struct comedi_device *dev)
{
	kref_init(&dev->refcount);
	spin_lock_init(&dev->spinlock);
	mutex_init(&dev->mutex);
	init_rwsem(&dev->attach_lock);
	dev->minor = -1;
}