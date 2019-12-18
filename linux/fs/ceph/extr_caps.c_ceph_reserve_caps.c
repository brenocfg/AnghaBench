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
struct ceph_mds_session {int s_nr_caps; int /*<<< orphan*/  s_mutex; } ;
struct ceph_mds_client {int caps_avail_count; int caps_reserve_count; int caps_total_count; int caps_use_count; int max_sessions; int /*<<< orphan*/  caps_list_lock; int /*<<< orphan*/  caps_list; int /*<<< orphan*/  mutex; } ;
struct ceph_cap_reservation {int count; scalar_t__ used; } ;
struct ceph_cap {int /*<<< orphan*/  caps_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct ceph_mds_session* __ceph_lookup_mds_session (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  __ceph_unreserve_caps (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  ceph_cap_cachep ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_trim_caps (struct ceph_mds_client*,struct ceph_mds_session*,int) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_cap_reservation*,int,...) ; 
 struct ceph_cap* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newcaps ; 
 int /*<<< orphan*/  pr_warn (char*,struct ceph_cap_reservation*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_reserve_caps(struct ceph_mds_client *mdsc,
		      struct ceph_cap_reservation *ctx, int need)
{
	int i, j;
	struct ceph_cap *cap;
	int have;
	int alloc = 0;
	int max_caps;
	int err = 0;
	bool trimmed = false;
	struct ceph_mds_session *s;
	LIST_HEAD(newcaps);

	dout("reserve caps ctx=%p need=%d\n", ctx, need);

	/* first reserve any caps that are already allocated */
	spin_lock(&mdsc->caps_list_lock);
	if (mdsc->caps_avail_count >= need)
		have = need;
	else
		have = mdsc->caps_avail_count;
	mdsc->caps_avail_count -= have;
	mdsc->caps_reserve_count += have;
	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
					 mdsc->caps_reserve_count +
					 mdsc->caps_avail_count);
	spin_unlock(&mdsc->caps_list_lock);

	for (i = have; i < need; ) {
		cap = kmem_cache_alloc(ceph_cap_cachep, GFP_NOFS);
		if (cap) {
			list_add(&cap->caps_item, &newcaps);
			alloc++;
			i++;
			continue;
		}

		if (!trimmed) {
			for (j = 0; j < mdsc->max_sessions; j++) {
				s = __ceph_lookup_mds_session(mdsc, j);
				if (!s)
					continue;
				mutex_unlock(&mdsc->mutex);

				mutex_lock(&s->s_mutex);
				max_caps = s->s_nr_caps - (need - i);
				ceph_trim_caps(mdsc, s, max_caps);
				mutex_unlock(&s->s_mutex);

				ceph_put_mds_session(s);
				mutex_lock(&mdsc->mutex);
			}
			trimmed = true;

			spin_lock(&mdsc->caps_list_lock);
			if (mdsc->caps_avail_count) {
				int more_have;
				if (mdsc->caps_avail_count >= need - i)
					more_have = need - i;
				else
					more_have = mdsc->caps_avail_count;

				i += more_have;
				have += more_have;
				mdsc->caps_avail_count -= more_have;
				mdsc->caps_reserve_count += more_have;

			}
			spin_unlock(&mdsc->caps_list_lock);

			continue;
		}

		pr_warn("reserve caps ctx=%p ENOMEM need=%d got=%d\n",
			ctx, need, have + alloc);
		err = -ENOMEM;
		break;
	}

	if (!err) {
		BUG_ON(have + alloc != need);
		ctx->count = need;
		ctx->used = 0;
	}

	spin_lock(&mdsc->caps_list_lock);
	mdsc->caps_total_count += alloc;
	mdsc->caps_reserve_count += alloc;
	list_splice(&newcaps, &mdsc->caps_list);

	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
					 mdsc->caps_reserve_count +
					 mdsc->caps_avail_count);

	if (err)
		__ceph_unreserve_caps(mdsc, have + alloc);

	spin_unlock(&mdsc->caps_list_lock);

	dout("reserve caps ctx=%p %d = %d used + %d resv + %d avail\n",
	     ctx, mdsc->caps_total_count, mdsc->caps_use_count,
	     mdsc->caps_reserve_count, mdsc->caps_avail_count);
	return err;
}