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
struct percpu_counter {int dummy; } ;
struct ext4_sb_info {int s_cluster_bits; int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; int /*<<< orphan*/  s_es; int /*<<< orphan*/  s_resv_clusters; struct percpu_counter s_dirtyclusters_counter; struct percpu_counter s_freeclusters_counter; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 scalar_t__ EXT4_FREECLUSTERS_WATERMARK ; 
 unsigned int EXT4_MB_USE_RESERVED ; 
 unsigned int EXT4_MB_USE_ROOT_BLOCKS ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int ext4_r_blocks_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_counter_read_positive (struct percpu_counter*) ; 
 scalar_t__ percpu_counter_sum_positive (struct percpu_counter*) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_has_free_clusters(struct ext4_sb_info *sbi,
				  s64 nclusters, unsigned int flags)
{
	s64 free_clusters, dirty_clusters, rsv, resv_clusters;
	struct percpu_counter *fcc = &sbi->s_freeclusters_counter;
	struct percpu_counter *dcc = &sbi->s_dirtyclusters_counter;

	free_clusters  = percpu_counter_read_positive(fcc);
	dirty_clusters = percpu_counter_read_positive(dcc);
	resv_clusters = atomic64_read(&sbi->s_resv_clusters);

	/*
	 * r_blocks_count should always be multiple of the cluster ratio so
	 * we are safe to do a plane bit shift only.
	 */
	rsv = (ext4_r_blocks_count(sbi->s_es) >> sbi->s_cluster_bits) +
	      resv_clusters;

	if (free_clusters - (nclusters + rsv + dirty_clusters) <
					EXT4_FREECLUSTERS_WATERMARK) {
		free_clusters  = percpu_counter_sum_positive(fcc);
		dirty_clusters = percpu_counter_sum_positive(dcc);
	}
	/* Check whether we have space after accounting for current
	 * dirty clusters & root reserved clusters.
	 */
	if (free_clusters >= (rsv + nclusters + dirty_clusters))
		return 1;

	/* Hm, nope.  Are (enough) root reserved clusters available? */
	if (uid_eq(sbi->s_resuid, current_fsuid()) ||
	    (!gid_eq(sbi->s_resgid, GLOBAL_ROOT_GID) && in_group_p(sbi->s_resgid)) ||
	    capable(CAP_SYS_RESOURCE) ||
	    (flags & EXT4_MB_USE_ROOT_BLOCKS)) {

		if (free_clusters >= (nclusters + dirty_clusters +
				      resv_clusters))
			return 1;
	}
	/* No free blocks. Let's see if we can dip into reserved pool */
	if (flags & EXT4_MB_USE_RESERVED) {
		if (free_clusters >= (nclusters + dirty_clusters))
			return 1;
	}

	return 0;
}