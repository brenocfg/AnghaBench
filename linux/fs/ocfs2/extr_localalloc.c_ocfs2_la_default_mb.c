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
struct super_block {int s_blocksize; } ;
struct ocfs2_super {int s_clustersize; unsigned int osb_clusters_at_boot; unsigned int max_slots; struct super_block* sb; int /*<<< orphan*/  s_feature_incompat; } ;

/* Variables and functions */
 unsigned int OCFS2_LA_MAX_DEFAULT_MB ; 
 unsigned int OCFS2_LA_OLD_DEFAULT ; 
 unsigned int ocfs2_clusters_to_megabytes (struct super_block*,int) ; 
 int ocfs2_group_bitmap_size (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_local_alloc_size (struct super_block*) ; 

unsigned int ocfs2_la_default_mb(struct ocfs2_super *osb)
{
	unsigned int la_mb;
	unsigned int gd_mb;
	unsigned int la_max_mb;
	unsigned int megs_per_slot;
	struct super_block *sb = osb->sb;

	gd_mb = ocfs2_clusters_to_megabytes(osb->sb,
		8 * ocfs2_group_bitmap_size(sb, 0, osb->s_feature_incompat));

	/*
	 * This takes care of files systems with very small group
	 * descriptors - 512 byte blocksize at cluster sizes lower
	 * than 16K and also 1k blocksize with 4k cluster size.
	 */
	if ((sb->s_blocksize == 512 && osb->s_clustersize <= 8192)
	    || (sb->s_blocksize == 1024 && osb->s_clustersize == 4096))
		return OCFS2_LA_OLD_DEFAULT;

	/*
	 * Leave enough room for some block groups and make the final
	 * value we work from a multiple of 4.
	 */
	gd_mb -= 16;
	gd_mb &= 0xFFFFFFFB;

	la_mb = gd_mb;

	/*
	 * Keep window sizes down to a reasonable default
	 */
	if (la_mb > OCFS2_LA_MAX_DEFAULT_MB) {
		/*
		 * Some clustersize / blocksize combinations will have
		 * given us a larger than OCFS2_LA_MAX_DEFAULT_MB
		 * default size, but get poor distribution when
		 * limited to exactly 256 megabytes.
		 *
		 * As an example, 16K clustersize at 4K blocksize
		 * gives us a cluster group size of 504M. Paring the
		 * local alloc size down to 256 however, would give us
		 * only one window and around 200MB left in the
		 * cluster group. Instead, find the first size below
		 * 256 which would give us an even distribution.
		 *
		 * Larger cluster group sizes actually work out pretty
		 * well when pared to 256, so we don't have to do this
		 * for any group that fits more than two
		 * OCFS2_LA_MAX_DEFAULT_MB windows.
		 */
		if (gd_mb > (2 * OCFS2_LA_MAX_DEFAULT_MB))
			la_mb = 256;
		else {
			unsigned int gd_mult = gd_mb;

			while (gd_mult > 256)
				gd_mult = gd_mult >> 1;

			la_mb = gd_mult;
		}
	}

	megs_per_slot = osb->osb_clusters_at_boot / osb->max_slots;
	megs_per_slot = ocfs2_clusters_to_megabytes(osb->sb, megs_per_slot);
	/* Too many nodes, too few disk clusters. */
	if (megs_per_slot < la_mb)
		la_mb = megs_per_slot;

	/* We can't store more bits than we can in a block. */
	la_max_mb = ocfs2_clusters_to_megabytes(osb->sb,
						ocfs2_local_alloc_size(sb) * 8);
	if (la_mb > la_max_mb)
		la_mb = la_max_mb;

	return la_mb;
}