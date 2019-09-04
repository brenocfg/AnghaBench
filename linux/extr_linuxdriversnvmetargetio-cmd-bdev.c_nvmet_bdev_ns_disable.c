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
struct nvmet_ns {int /*<<< orphan*/ * bdev; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int) ; 

void nvmet_bdev_ns_disable(struct nvmet_ns *ns)
{
	if (ns->bdev) {
		blkdev_put(ns->bdev, FMODE_WRITE | FMODE_READ);
		ns->bdev = NULL;
	}
}