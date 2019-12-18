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
struct ceph_mds_client {int /*<<< orphan*/  cap_reclaim_work; TYPE_1__* fsc; scalar_t__ stopping; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dout (char*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_queue_cap_reclaim_work(struct ceph_mds_client *mdsc)
{
	if (mdsc->stopping)
		return;

        if (queue_work(mdsc->fsc->cap_wq, &mdsc->cap_reclaim_work)) {
                dout("caps reclaim work queued\n");
        } else {
                dout("failed to queue caps release work\n");
        }
}