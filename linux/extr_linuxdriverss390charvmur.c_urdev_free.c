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
struct urdev {TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct urdev*) ; 
 int /*<<< orphan*/  kfree (struct urdev*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void urdev_free(struct urdev *urd)
{
	TRACE("urdev_free: %p\n", urd);
	if (urd->cdev)
		put_device(&urd->cdev->dev);
	kfree(urd);
}