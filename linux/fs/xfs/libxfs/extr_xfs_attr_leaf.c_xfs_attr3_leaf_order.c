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
struct xfs_buf {int /*<<< orphan*/  b_addr; } ;
struct xfs_attr_leaf_entry {int /*<<< orphan*/  hashval; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_attr3_leaf_order(
	struct xfs_buf	*leaf1_bp,
	struct xfs_attr3_icleaf_hdr *leaf1hdr,
	struct xfs_buf	*leaf2_bp,
	struct xfs_attr3_icleaf_hdr *leaf2hdr)
{
	struct xfs_attr_leaf_entry *entries1;
	struct xfs_attr_leaf_entry *entries2;

	entries1 = xfs_attr3_leaf_entryp(leaf1_bp->b_addr);
	entries2 = xfs_attr3_leaf_entryp(leaf2_bp->b_addr);
	if (leaf1hdr->count > 0 && leaf2hdr->count > 0 &&
	    ((be32_to_cpu(entries2[0].hashval) <
	      be32_to_cpu(entries1[0].hashval)) ||
	     (be32_to_cpu(entries2[leaf2hdr->count - 1].hashval) <
	      be32_to_cpu(entries1[leaf1hdr->count - 1].hashval)))) {
		return 1;
	}
	return 0;
}