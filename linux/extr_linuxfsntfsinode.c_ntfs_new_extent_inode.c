#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_5__ {unsigned long mft_no; scalar_t__ name_len; int /*<<< orphan*/ * name; int /*<<< orphan*/  type; int /*<<< orphan*/  mrec_lock; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  AT_UNUSED ; 
 int /*<<< orphan*/  __ntfs_init_inode (struct super_block*,TYPE_1__*) ; 
 int /*<<< orphan*/  extent_inode_mrec_lock_key ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ntfs_alloc_extent_inode () ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 

inline ntfs_inode *ntfs_new_extent_inode(struct super_block *sb,
		unsigned long mft_no)
{
	ntfs_inode *ni = ntfs_alloc_extent_inode();

	ntfs_debug("Entering.");
	if (likely(ni != NULL)) {
		__ntfs_init_inode(sb, ni);
		lockdep_set_class(&ni->mrec_lock, &extent_inode_mrec_lock_key);
		ni->mft_no = mft_no;
		ni->type = AT_UNUSED;
		ni->name = NULL;
		ni->name_len = 0;
	}
	return ni;
}