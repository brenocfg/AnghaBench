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
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_clear_claiming (struct block_device*,void*) ; 
 int /*<<< orphan*/  bdev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bd_abort_claiming(struct block_device *bdev, struct block_device *whole,
		       void *holder)
{
	spin_lock(&bdev_lock);
	bd_clear_claiming(whole, holder);
	spin_unlock(&bdev_lock);
}