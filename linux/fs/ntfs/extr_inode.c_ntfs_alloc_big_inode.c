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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct inode* VFS_I (TYPE_1__*) ; 
 TYPE_1__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_big_inode_cache ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*) ; 

struct inode *ntfs_alloc_big_inode(struct super_block *sb)
{
	ntfs_inode *ni;

	ntfs_debug("Entering.");
	ni = kmem_cache_alloc(ntfs_big_inode_cache, GFP_NOFS);
	if (likely(ni != NULL)) {
		ni->state = 0;
		return VFS_I(ni);
	}
	ntfs_error(sb, "Allocation of NTFS big inode structure failed.");
	return NULL;
}