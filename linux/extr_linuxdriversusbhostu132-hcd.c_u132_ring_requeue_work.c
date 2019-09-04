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
struct u132_ring {int /*<<< orphan*/  scheduler; } ;
struct u132 {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  u132_hcd_delete ; 
 int /*<<< orphan*/  workqueue ; 

__attribute__((used)) static void u132_ring_requeue_work(struct u132 *u132, struct u132_ring *ring,
	unsigned int delta)
{
	if (delta > 0) {
		if (queue_delayed_work(workqueue, &ring->scheduler, delta))
			return;
	} else if (queue_delayed_work(workqueue, &ring->scheduler, 0))
		return;
	kref_put(&u132->kref, u132_hcd_delete);
}