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
typedef  int u8 ;
struct ceph_pg_pool_info {int size; int min_size; int read_tier; int write_tier; void* last_force_request_resend; void* flags; void* pgp_num; void* pg_num; void* object_hash; void* crush_ruleset; void* type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  calc_pg_masks (struct ceph_pg_pool_info*) ; 
 void* ceph_decode_32 (void**) ; 
 void* ceph_decode_64 (void**) ; 
 void* ceph_decode_8 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static int decode_pool(void **p, void *end, struct ceph_pg_pool_info *pi)
{
	u8 ev, cv;
	unsigned len, num;
	void *pool_end;

	ceph_decode_need(p, end, 2 + 4, bad);
	ev = ceph_decode_8(p);  /* encoding version */
	cv = ceph_decode_8(p); /* compat version */
	if (ev < 5) {
		pr_warn("got v %d < 5 cv %d of ceph_pg_pool\n", ev, cv);
		return -EINVAL;
	}
	if (cv > 9) {
		pr_warn("got v %d cv %d > 9 of ceph_pg_pool\n", ev, cv);
		return -EINVAL;
	}
	len = ceph_decode_32(p);
	ceph_decode_need(p, end, len, bad);
	pool_end = *p + len;

	pi->type = ceph_decode_8(p);
	pi->size = ceph_decode_8(p);
	pi->crush_ruleset = ceph_decode_8(p);
	pi->object_hash = ceph_decode_8(p);

	pi->pg_num = ceph_decode_32(p);
	pi->pgp_num = ceph_decode_32(p);

	*p += 4 + 4;  /* skip lpg* */
	*p += 4;      /* skip last_change */
	*p += 8 + 4;  /* skip snap_seq, snap_epoch */

	/* skip snaps */
	num = ceph_decode_32(p);
	while (num--) {
		*p += 8;  /* snapid key */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;
	}

	/* skip removed_snaps */
	num = ceph_decode_32(p);
	*p += num * (8 + 8);

	*p += 8;  /* skip auid */
	pi->flags = ceph_decode_64(p);
	*p += 4;  /* skip crash_replay_interval */

	if (ev >= 7)
		pi->min_size = ceph_decode_8(p);
	else
		pi->min_size = pi->size - pi->size / 2;

	if (ev >= 8)
		*p += 8 + 8;  /* skip quota_max_* */

	if (ev >= 9) {
		/* skip tiers */
		num = ceph_decode_32(p);
		*p += num * 8;

		*p += 8;  /* skip tier_of */
		*p += 1;  /* skip cache_mode */

		pi->read_tier = ceph_decode_64(p);
		pi->write_tier = ceph_decode_64(p);
	} else {
		pi->read_tier = -1;
		pi->write_tier = -1;
	}

	if (ev >= 10) {
		/* skip properties */
		num = ceph_decode_32(p);
		while (num--) {
			len = ceph_decode_32(p);
			*p += len; /* key */
			len = ceph_decode_32(p);
			*p += len; /* val */
		}
	}

	if (ev >= 11) {
		/* skip hit_set_params */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;

		*p += 4; /* skip hit_set_period */
		*p += 4; /* skip hit_set_count */
	}

	if (ev >= 12)
		*p += 4; /* skip stripe_width */

	if (ev >= 13) {
		*p += 8; /* skip target_max_bytes */
		*p += 8; /* skip target_max_objects */
		*p += 4; /* skip cache_target_dirty_ratio_micro */
		*p += 4; /* skip cache_target_full_ratio_micro */
		*p += 4; /* skip cache_min_flush_age */
		*p += 4; /* skip cache_min_evict_age */
	}

	if (ev >=  14) {
		/* skip erasure_code_profile */
		len = ceph_decode_32(p);
		*p += len;
	}

	/*
	 * last_force_op_resend_preluminous, will be overridden if the
	 * map was encoded with RESEND_ON_SPLIT
	 */
	if (ev >= 15)
		pi->last_force_request_resend = ceph_decode_32(p);
	else
		pi->last_force_request_resend = 0;

	if (ev >= 16)
		*p += 4; /* skip min_read_recency_for_promote */

	if (ev >= 17)
		*p += 8; /* skip expected_num_objects */

	if (ev >= 19)
		*p += 4; /* skip cache_target_dirty_high_ratio_micro */

	if (ev >= 20)
		*p += 4; /* skip min_write_recency_for_promote */

	if (ev >= 21)
		*p += 1; /* skip use_gmt_hitset */

	if (ev >= 22)
		*p += 1; /* skip fast_read */

	if (ev >= 23) {
		*p += 4; /* skip hit_set_grade_decay_rate */
		*p += 4; /* skip hit_set_search_last_n */
	}

	if (ev >= 24) {
		/* skip opts */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;
	}

	if (ev >= 25)
		pi->last_force_request_resend = ceph_decode_32(p);

	/* ignore the rest */

	*p = pool_end;
	calc_pg_masks(pi);
	return 0;

bad:
	return -EINVAL;
}