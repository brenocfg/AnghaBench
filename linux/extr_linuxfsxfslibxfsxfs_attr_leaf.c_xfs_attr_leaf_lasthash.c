#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dahash_t ;
struct xfs_mount {int /*<<< orphan*/  m_attr_geo; } ;
struct xfs_buf {int /*<<< orphan*/  b_addr; TYPE_1__* b_target; } ;
struct xfs_attr_leaf_entry {int /*<<< orphan*/  hashval; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;
struct TYPE_2__ {struct xfs_mount* bt_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,int /*<<< orphan*/ ) ; 

xfs_dahash_t
xfs_attr_leaf_lasthash(
	struct xfs_buf	*bp,
	int		*count)
{
	struct xfs_attr3_icleaf_hdr ichdr;
	struct xfs_attr_leaf_entry *entries;
	struct xfs_mount *mp = bp->b_target->bt_mount;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, bp->b_addr);
	entries = xfs_attr3_leaf_entryp(bp->b_addr);
	if (count)
		*count = ichdr.count;
	if (!ichdr.count)
		return 0;
	return be32_to_cpu(entries[ichdr.count - 1].hashval);
}