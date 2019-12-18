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
struct ceph_snapid_map {int /*<<< orphan*/  lru; int /*<<< orphan*/  last_used; int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct ceph_mds_client {int /*<<< orphan*/  snapid_map_lock; int /*<<< orphan*/  snapid_map_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct ceph_snapid_map*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_put_snapid_map(struct ceph_mds_client* mdsc,
			 struct ceph_snapid_map *sm)
{
	if (!sm)
		return;
	if (atomic_dec_and_lock(&sm->ref, &mdsc->snapid_map_lock)) {
		if (!RB_EMPTY_NODE(&sm->node)) {
			sm->last_used = jiffies;
			list_add_tail(&sm->lru, &mdsc->snapid_map_lru);
			spin_unlock(&mdsc->snapid_map_lock);
		} else {
			/* already cleaned up by
			 * ceph_cleanup_snapid_map() */
			spin_unlock(&mdsc->snapid_map_lock);
			kfree(sm);
		}
	}
}