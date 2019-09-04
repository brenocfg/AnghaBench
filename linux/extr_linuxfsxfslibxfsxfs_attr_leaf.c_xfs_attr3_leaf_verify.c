#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_5__* m_attr_geo; TYPE_4__ m_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  lsn; int /*<<< orphan*/  blkno; int /*<<< orphan*/  uuid; } ;
struct xfs_da3_node_hdr {TYPE_2__ info; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_da3_node_hdr* b_addr; TYPE_1__* b_target; } ;
struct xfs_attr_leafblock {TYPE_2__ info; } ;
struct xfs_attr_leaf_entry {int dummy; } ;
struct xfs_attr3_icleaf_hdr {scalar_t__ magic; size_t count; scalar_t__ firstused; TYPE_3__* freemap; } ;
struct TYPE_10__ {scalar_t__ blksize; } ;
struct TYPE_8__ {int base; int size; } ;
struct TYPE_6__ {struct xfs_mount* bt_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_ATTR3_LEAF_MAGIC ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LEAF_MAPSIZE ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (struct xfs_da3_node_hdr*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (TYPE_5__*,struct xfs_attr3_icleaf_hdr*,struct xfs_da3_node_hdr*) ; 
 scalar_t__ xfs_attr3_leaf_hdr_size (struct xfs_da3_node_hdr*) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_log_in_recovery (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_4__*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_attr3_leaf_verify(
	struct xfs_buf			*bp)
{
	struct xfs_attr3_icleaf_hdr	ichdr;
	struct xfs_mount		*mp = bp->b_target->bt_mount;
	struct xfs_attr_leafblock	*leaf = bp->b_addr;
	struct xfs_attr_leaf_entry	*entries;
	uint32_t			end;	/* must be 32bit - see below */
	int				i;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, leaf);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_da3_node_hdr *hdr3 = bp->b_addr;

		if (ichdr.magic != XFS_ATTR3_LEAF_MAGIC)
			return __this_address;

		if (!uuid_equal(&hdr3->info.uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (be64_to_cpu(hdr3->info.blkno) != bp->b_bn)
			return __this_address;
		if (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->info.lsn)))
			return __this_address;
	} else {
		if (ichdr.magic != XFS_ATTR_LEAF_MAGIC)
			return __this_address;
	}
	/*
	 * In recovery there is a transient state where count == 0 is valid
	 * because we may have transitioned an empty shortform attr to a leaf
	 * if the attr didn't fit in shortform.
	 */
	if (!xfs_log_in_recovery(mp) && ichdr.count == 0)
		return __this_address;

	/*
	 * firstused is the block offset of the first name info structure.
	 * Make sure it doesn't go off the block or crash into the header.
	 */
	if (ichdr.firstused > mp->m_attr_geo->blksize)
		return __this_address;
	if (ichdr.firstused < xfs_attr3_leaf_hdr_size(leaf))
		return __this_address;

	/* Make sure the entries array doesn't crash into the name info. */
	entries = xfs_attr3_leaf_entryp(bp->b_addr);
	if ((char *)&entries[ichdr.count] >
	    (char *)bp->b_addr + ichdr.firstused)
		return __this_address;

	/* XXX: need to range check rest of attr header values */
	/* XXX: hash order check? */

	/*
	 * Quickly check the freemap information.  Attribute data has to be
	 * aligned to 4-byte boundaries, and likewise for the free space.
	 *
	 * Note that for 64k block size filesystems, the freemap entries cannot
	 * overflow as they are only be16 fields. However, when checking end
	 * pointer of the freemap, we have to be careful to detect overflows and
	 * so use uint32_t for those checks.
	 */
	for (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) {
		if (ichdr.freemap[i].base > mp->m_attr_geo->blksize)
			return __this_address;
		if (ichdr.freemap[i].base & 0x3)
			return __this_address;
		if (ichdr.freemap[i].size > mp->m_attr_geo->blksize)
			return __this_address;
		if (ichdr.freemap[i].size & 0x3)
			return __this_address;

		/* be care of 16 bit overflows here */
		end = (uint32_t)ichdr.freemap[i].base + ichdr.freemap[i].size;
		if (end < ichdr.freemap[i].base)
			return __this_address;
		if (end > mp->m_attr_geo->blksize)
			return __this_address;
	}

	return NULL;
}