#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_1__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ntfs_inode_cache ; 

__attribute__((used)) static inline ntfs_inode *ntfs_alloc_extent_inode(void)
{
	ntfs_inode *ni;

	ntfs_debug("Entering.");
	ni = kmem_cache_alloc(ntfs_inode_cache, GFP_NOFS);
	if (likely(ni != NULL)) {
		ni->state = 0;
		return ni;
	}
	ntfs_error(NULL, "Allocation of NTFS inode structure failed.");
	return NULL;
}