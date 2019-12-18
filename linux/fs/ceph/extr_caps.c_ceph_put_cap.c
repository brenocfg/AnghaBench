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
struct ceph_mds_client {scalar_t__ caps_total_count; scalar_t__ caps_use_count; scalar_t__ caps_reserve_count; scalar_t__ caps_avail_count; scalar_t__ caps_min_count; int /*<<< orphan*/  caps_list_lock; int /*<<< orphan*/  caps_list; } ;
struct ceph_cap {int /*<<< orphan*/  caps_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ceph_cap_cachep ; 
 int /*<<< orphan*/  dout (char*,struct ceph_cap*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ceph_cap*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_put_cap(struct ceph_mds_client *mdsc, struct ceph_cap *cap)
{
	spin_lock(&mdsc->caps_list_lock);
	dout("put_cap %p %d = %d used + %d resv + %d avail\n",
	     cap, mdsc->caps_total_count, mdsc->caps_use_count,
	     mdsc->caps_reserve_count, mdsc->caps_avail_count);
	mdsc->caps_use_count--;
	/*
	 * Keep some preallocated caps around (ceph_min_count), to
	 * avoid lots of free/alloc churn.
	 */
	if (mdsc->caps_avail_count >= mdsc->caps_reserve_count +
				      mdsc->caps_min_count) {
		mdsc->caps_total_count--;
		kmem_cache_free(ceph_cap_cachep, cap);
	} else {
		mdsc->caps_avail_count++;
		list_add(&cap->caps_item, &mdsc->caps_list);
	}

	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
	       mdsc->caps_reserve_count + mdsc->caps_avail_count);
	spin_unlock(&mdsc->caps_list_lock);
}