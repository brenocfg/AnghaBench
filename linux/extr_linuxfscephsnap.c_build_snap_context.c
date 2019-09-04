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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct list_head {int dummy; } ;
struct ceph_snap_realm {int num_prior_parent_snaps; int num_snaps; scalar_t__ seq; scalar_t__ parent_since; int /*<<< orphan*/  ino; struct ceph_snap_context* cached_context; int /*<<< orphan*/  dirty_item; int /*<<< orphan*/  prior_parent_snaps; int /*<<< orphan*/  snaps; struct ceph_snap_realm* parent; } ;
struct ceph_snap_context {int num_snaps; scalar_t__ seq; scalar_t__* snaps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int SIZE_MAX ; 
 struct ceph_snap_context* ceph_create_snap_context (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_snap_context (struct ceph_snap_context*) ; 
 int /*<<< orphan*/  cmpu64_rev ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_snap_realm*,struct ceph_snap_context*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,struct ceph_snap_realm*,int) ; 
 int /*<<< orphan*/  sort (scalar_t__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_snap_context(struct ceph_snap_realm *realm,
			      struct list_head* dirty_realms)
{
	struct ceph_snap_realm *parent = realm->parent;
	struct ceph_snap_context *snapc;
	int err = 0;
	u32 num = realm->num_prior_parent_snaps + realm->num_snaps;

	/*
	 * build parent context, if it hasn't been built.
	 * conservatively estimate that all parent snaps might be
	 * included by us.
	 */
	if (parent) {
		if (!parent->cached_context) {
			err = build_snap_context(parent, dirty_realms);
			if (err)
				goto fail;
		}
		num += parent->cached_context->num_snaps;
	}

	/* do i actually need to update?  not if my context seq
	   matches realm seq, and my parents' does to.  (this works
	   because we rebuild_snap_realms() works _downward_ in
	   hierarchy after each update.) */
	if (realm->cached_context &&
	    realm->cached_context->seq == realm->seq &&
	    (!parent ||
	     realm->cached_context->seq >= parent->cached_context->seq)) {
		dout("build_snap_context %llx %p: %p seq %lld (%u snaps)"
		     " (unchanged)\n",
		     realm->ino, realm, realm->cached_context,
		     realm->cached_context->seq,
		     (unsigned int)realm->cached_context->num_snaps);
		return 0;
	}

	/* alloc new snap context */
	err = -ENOMEM;
	if (num > (SIZE_MAX - sizeof(*snapc)) / sizeof(u64))
		goto fail;
	snapc = ceph_create_snap_context(num, GFP_NOFS);
	if (!snapc)
		goto fail;

	/* build (reverse sorted) snap vector */
	num = 0;
	snapc->seq = realm->seq;
	if (parent) {
		u32 i;

		/* include any of parent's snaps occurring _after_ my
		   parent became my parent */
		for (i = 0; i < parent->cached_context->num_snaps; i++)
			if (parent->cached_context->snaps[i] >=
			    realm->parent_since)
				snapc->snaps[num++] =
					parent->cached_context->snaps[i];
		if (parent->cached_context->seq > snapc->seq)
			snapc->seq = parent->cached_context->seq;
	}
	memcpy(snapc->snaps + num, realm->snaps,
	       sizeof(u64)*realm->num_snaps);
	num += realm->num_snaps;
	memcpy(snapc->snaps + num, realm->prior_parent_snaps,
	       sizeof(u64)*realm->num_prior_parent_snaps);
	num += realm->num_prior_parent_snaps;

	sort(snapc->snaps, num, sizeof(u64), cmpu64_rev, NULL);
	snapc->num_snaps = num;
	dout("build_snap_context %llx %p: %p seq %lld (%u snaps)\n",
	     realm->ino, realm, snapc, snapc->seq,
	     (unsigned int) snapc->num_snaps);

	ceph_put_snap_context(realm->cached_context);
	realm->cached_context = snapc;
	/* queue realm for cap_snap creation */
	list_add_tail(&realm->dirty_item, dirty_realms);
	return 0;

fail:
	/*
	 * if we fail, clear old (incorrect) cached_context... hopefully
	 * we'll have better luck building it later
	 */
	if (realm->cached_context) {
		ceph_put_snap_context(realm->cached_context);
		realm->cached_context = NULL;
	}
	pr_err("build_snap_context %llx %p fail %d\n", realm->ino,
	       realm, err);
	return err;
}