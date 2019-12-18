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
struct virtio_fs_vq {scalar_t__ in_flight; int /*<<< orphan*/  dispatch_work; int /*<<< orphan*/  done_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void virtio_fs_drain_queue(struct virtio_fs_vq *fsvq)
{
	WARN_ON(fsvq->in_flight < 0);

	/* Wait for in flight requests to finish.*/
	while (1) {
		spin_lock(&fsvq->lock);
		if (!fsvq->in_flight) {
			spin_unlock(&fsvq->lock);
			break;
		}
		spin_unlock(&fsvq->lock);
		/* TODO use completion instead of timeout */
		usleep_range(1000, 2000);
	}

	flush_work(&fsvq->done_work);
	flush_delayed_work(&fsvq->dispatch_work);
}