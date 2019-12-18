#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ namelen; int /*<<< orphan*/  valuelen; } ;
typedef  TYPE_3__ xfs_attr_leaf_name_local_t ;
struct xfs_mount {int /*<<< orphan*/  m_attr_geo; } ;
struct TYPE_6__ {scalar_t__ di_format; } ;
struct xfs_inode {TYPE_2__ i_d; TYPE_1__* i_mount; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; struct xfs_mount* b_mount; } ;
struct xfs_attr_sf_hdr {int dummy; } ;
struct xfs_attr_sf_entry {int dummy; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr_leaf_entry {int flags; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;
struct TYPE_5__ {int m_flags; } ;

/* Variables and functions */
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LOCAL ; 
 scalar_t__ XFS_ATTR_SF_ENTSIZE_MAX ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 int XFS_MOUNT_ATTR2 ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 TYPE_3__* xfs_attr3_leaf_name_local (struct xfs_attr_leafblock*,int) ; 
 int xfs_attr_shortform_bytesfit (struct xfs_inode*,int) ; 

int
xfs_attr_shortform_allfit(
	struct xfs_buf		*bp,
	struct xfs_inode	*dp)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr_leaf_entry *entry;
	xfs_attr_leaf_name_local_t *name_loc;
	struct xfs_attr3_icleaf_hdr leafhdr;
	int			bytes;
	int			i;
	struct xfs_mount	*mp = bp->b_mount;

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &leafhdr, leaf);
	entry = xfs_attr3_leaf_entryp(leaf);

	bytes = sizeof(struct xfs_attr_sf_hdr);
	for (i = 0; i < leafhdr.count; entry++, i++) {
		if (entry->flags & XFS_ATTR_INCOMPLETE)
			continue;		/* don't copy partial entries */
		if (!(entry->flags & XFS_ATTR_LOCAL))
			return 0;
		name_loc = xfs_attr3_leaf_name_local(leaf, i);
		if (name_loc->namelen >= XFS_ATTR_SF_ENTSIZE_MAX)
			return 0;
		if (be16_to_cpu(name_loc->valuelen) >= XFS_ATTR_SF_ENTSIZE_MAX)
			return 0;
		bytes += sizeof(struct xfs_attr_sf_entry) - 1
				+ name_loc->namelen
				+ be16_to_cpu(name_loc->valuelen);
	}
	if ((dp->i_mount->m_flags & XFS_MOUNT_ATTR2) &&
	    (dp->i_d.di_format != XFS_DINODE_FMT_BTREE) &&
	    (bytes == sizeof(struct xfs_attr_sf_hdr)))
		return -1;
	return xfs_attr_shortform_bytesfit(dp, bytes);
}