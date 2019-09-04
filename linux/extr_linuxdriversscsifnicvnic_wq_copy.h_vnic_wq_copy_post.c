#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ desc_count; int /*<<< orphan*/  desc_avail; } ;
struct vnic_wq_copy {scalar_t__ to_use_index; TYPE_2__* ctrl; TYPE_1__ ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  posted_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void vnic_wq_copy_post(struct vnic_wq_copy *wq)
{

	((wq->to_use_index + 1) == wq->ring.desc_count) ?
		(wq->to_use_index = 0) : (wq->to_use_index++);
	wq->ring.desc_avail--;

	/* Adding write memory barrier prevents compiler and/or CPU
	 * reordering, thus avoiding descriptor posting before
	 * descriptor is initialized. Otherwise, hardware can read
	 * stale descriptor fields.
	 */
	wmb();

	iowrite32(wq->to_use_index, &wq->ctrl->posted_index);
}