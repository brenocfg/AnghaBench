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
struct ceph_mds_client {int /*<<< orphan*/  cap_reclaim_pending; } ;

/* Variables and functions */
 int CEPH_CAPS_PER_RELEASE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_queue_cap_reclaim_work (struct ceph_mds_client*) ; 

void ceph_reclaim_caps_nr(struct ceph_mds_client *mdsc, int nr)
{
	int val;
	if (!nr)
		return;
	val = atomic_add_return(nr, &mdsc->cap_reclaim_pending);
	if (!(val % CEPH_CAPS_PER_RELEASE)) {
		atomic_set(&mdsc->cap_reclaim_pending, 0);
		ceph_queue_cap_reclaim_work(mdsc);
	}
}