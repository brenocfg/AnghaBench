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
struct gntdev_copy_batch {unsigned int nr_ops; int /*<<< orphan*/ * status; TYPE_1__* ops; } ;
typedef  scalar_t__ s16 ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ GNTST_okay ; 
 scalar_t__ __get_user (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ __put_user (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gntdev_put_pages (struct gntdev_copy_batch*) ; 
 int /*<<< orphan*/  gnttab_batch_copy (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int gntdev_copy(struct gntdev_copy_batch *batch)
{
	unsigned int i;

	gnttab_batch_copy(batch->ops, batch->nr_ops);
	gntdev_put_pages(batch);

	/*
	 * For each completed op, update the status if the op failed
	 * and all previous ops for the segment were successful.
	 */
	for (i = 0; i < batch->nr_ops; i++) {
		s16 status = batch->ops[i].status;
		s16 old_status;

		if (status == GNTST_okay)
			continue;

		if (__get_user(old_status, batch->status[i]))
			return -EFAULT;

		if (old_status != GNTST_okay)
			continue;

		if (__put_user(status, batch->status[i]))
			return -EFAULT;
	}

	batch->nr_ops = 0;
	return 0;
}