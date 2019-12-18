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
typedef  int /*<<< orphan*/  xfs_attr_leafblock_t ;
struct xfs_attr_leaf_entry {int /*<<< orphan*/  nameidx; } ;

/* Variables and functions */
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline char *
xfs_attr3_leaf_name(xfs_attr_leafblock_t *leafp, int idx)
{
	struct xfs_attr_leaf_entry *entries = xfs_attr3_leaf_entryp(leafp);

	return &((char *)leafp)[be16_to_cpu(entries[idx].nameidx)];
}