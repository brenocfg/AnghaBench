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
struct rds_ib_device {int /*<<< orphan*/  free_work; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_wq ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

void rds_ib_dev_put(struct rds_ib_device *rds_ibdev)
{
	BUG_ON(refcount_read(&rds_ibdev->refcount) == 0);
	if (refcount_dec_and_test(&rds_ibdev->refcount))
		queue_work(rds_wq, &rds_ibdev->free_work);
}