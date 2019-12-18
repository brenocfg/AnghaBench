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
struct xfs_mount {int /*<<< orphan*/  m_attr_geo; } ;
struct xfs_buf {int /*<<< orphan*/  b_addr; struct xfs_mount* b_mount; } ;
struct xfs_attr3_icleaf_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,int /*<<< orphan*/ ) ; 
 int xfs_attr3_leaf_order (struct xfs_buf*,struct xfs_attr3_icleaf_hdr*,struct xfs_buf*,struct xfs_attr3_icleaf_hdr*) ; 

int
xfs_attr_leaf_order(
	struct xfs_buf	*leaf1_bp,
	struct xfs_buf	*leaf2_bp)
{
	struct xfs_attr3_icleaf_hdr ichdr1;
	struct xfs_attr3_icleaf_hdr ichdr2;
	struct xfs_mount *mp = leaf1_bp->b_mount;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr1, leaf1_bp->b_addr);
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr2, leaf2_bp->b_addr);
	return xfs_attr3_leaf_order(leaf1_bp, &ichdr1, leaf2_bp, &ichdr2);
}