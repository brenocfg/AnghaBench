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
typedef  int /*<<< orphan*/  u8 ;
struct bcm2048_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int bcm2048_set_rds_no_lock (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_rds(struct bcm2048_device *bdev, u8 rds_on)
{
	int err;

	mutex_lock(&bdev->mutex);

	err = bcm2048_set_rds_no_lock(bdev, rds_on);

	mutex_unlock(&bdev->mutex);
	return err;
}