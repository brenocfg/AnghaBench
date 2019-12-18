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
struct ceph_mds_client {scalar_t__ caps_use_max; scalar_t__ caps_use_count; int /*<<< orphan*/  caps_list_lock; } ;
struct ceph_cap_reservation {int /*<<< orphan*/  used; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ceph_unreserve_caps (struct ceph_mds_client*,scalar_t__) ; 
 int /*<<< orphan*/  ceph_reclaim_caps_nr (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_cap_reservation*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_unreserve_caps(struct ceph_mds_client *mdsc,
			 struct ceph_cap_reservation *ctx)
{
	bool reclaim = false;
	if (!ctx->count)
		return;

	dout("unreserve caps ctx=%p count=%d\n", ctx, ctx->count);
	spin_lock(&mdsc->caps_list_lock);
	__ceph_unreserve_caps(mdsc, ctx->count);
	ctx->count = 0;

	if (mdsc->caps_use_max > 0 &&
	    mdsc->caps_use_count > mdsc->caps_use_max)
		reclaim = true;
	spin_unlock(&mdsc->caps_list_lock);

	if (reclaim)
		ceph_reclaim_caps_nr(mdsc, ctx->used);
}