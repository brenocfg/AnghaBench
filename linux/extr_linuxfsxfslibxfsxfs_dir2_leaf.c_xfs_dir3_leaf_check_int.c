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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_tail_t ;
struct xfs_mount {struct xfs_da_geometry* m_dir_geo; } ;
struct xfs_inode {int dummy; } ;
struct xfs_dir_ops {size_t (* leaf_max_ents ) (struct xfs_da_geometry*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (struct xfs_dir2_leaf*) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ;} ;
struct xfs_dir3_icleaf_hdr {size_t count; scalar_t__ magic; int stale; } ;
struct xfs_dir2_leaf_entry {scalar_t__ address; int /*<<< orphan*/  hashval; } ;
struct xfs_dir2_leaf {int dummy; } ;
struct xfs_da_geometry {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ; 
 struct xfs_dir2_leaf_entry* stub2 (struct xfs_dir2_leaf*) ; 
 size_t stub3 (struct xfs_da_geometry*) ; 
 scalar_t__ xfs_dir2_leaf_bests_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_leaf_tail_p (struct xfs_da_geometry*,struct xfs_dir2_leaf*) ; 
 struct xfs_dir_ops* xfs_dir_get_ops (struct xfs_mount*,struct xfs_inode*) ; 

xfs_failaddr_t
xfs_dir3_leaf_check_int(
	struct xfs_mount	*mp,
	struct xfs_inode	*dp,
	struct xfs_dir3_icleaf_hdr *hdr,
	struct xfs_dir2_leaf	*leaf)
{
	struct xfs_dir2_leaf_entry *ents;
	xfs_dir2_leaf_tail_t	*ltp;
	int			stale;
	int			i;
	const struct xfs_dir_ops *ops;
	struct xfs_dir3_icleaf_hdr leafhdr;
	struct xfs_da_geometry	*geo = mp->m_dir_geo;

	/*
	 * we can be passed a null dp here from a verifier, so we need to go the
	 * hard way to get them.
	 */
	ops = xfs_dir_get_ops(mp, dp);

	if (!hdr) {
		ops->leaf_hdr_from_disk(&leafhdr, leaf);
		hdr = &leafhdr;
	}

	ents = ops->leaf_ents_p(leaf);
	ltp = xfs_dir2_leaf_tail_p(geo, leaf);

	/*
	 * XXX (dgc): This value is not restrictive enough.
	 * Should factor in the size of the bests table as well.
	 * We can deduce a value for that from di_size.
	 */
	if (hdr->count > ops->leaf_max_ents(geo))
		return __this_address;

	/* Leaves and bests don't overlap in leaf format. */
	if ((hdr->magic == XFS_DIR2_LEAF1_MAGIC ||
	     hdr->magic == XFS_DIR3_LEAF1_MAGIC) &&
	    (char *)&ents[hdr->count] > (char *)xfs_dir2_leaf_bests_p(ltp))
		return __this_address;

	/* Check hash value order, count stale entries.  */
	for (i = stale = 0; i < hdr->count; i++) {
		if (i + 1 < hdr->count) {
			if (be32_to_cpu(ents[i].hashval) >
					be32_to_cpu(ents[i + 1].hashval))
				return __this_address;
		}
		if (ents[i].address == cpu_to_be32(XFS_DIR2_NULL_DATAPTR))
			stale++;
	}
	if (hdr->stale != stale)
		return __this_address;
	return NULL;
}