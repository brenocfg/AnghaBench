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
struct knav_range_info {int num_queues; int flags; struct knav_acc_channel* acc; struct knav_device* kdev; } ;
struct knav_device {int dummy; } ;
struct knav_acc_channel {scalar_t__ list_index; } ;
typedef  enum knav_acc_result { ____Placeholder_knav_acc_result } knav_acc_result ;

/* Variables and functions */
 int ACC_RET_SUCCESS ; 
 int EIO ; 
 int RANGE_MULTI_QUEUE ; 
 int knav_acc_start (struct knav_device*,struct knav_range_info*,int) ; 
 int /*<<< orphan*/  knav_acc_stop (struct knav_device*,struct knav_range_info*,int) ; 

__attribute__((used)) static int knav_acc_init_range(struct knav_range_info *range)
{
	struct knav_device *kdev = range->kdev;
	struct knav_acc_channel *acc;
	enum knav_acc_result result;
	int queue;

	for (queue = 0; queue < range->num_queues; queue++) {
		acc = range->acc + queue;

		knav_acc_stop(kdev, range, queue);
		acc->list_index = 0;
		result = knav_acc_start(kdev, range, queue);

		if (result != ACC_RET_SUCCESS)
			return -EIO;

		if (range->flags & RANGE_MULTI_QUEUE)
			return 0;
	}
	return 0;
}