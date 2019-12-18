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
struct inode {scalar_t__ i_default_acl; scalar_t__ i_acl; TYPE_1__* i_sb; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_remove_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_inode_delete (struct inode*) ; 
 int /*<<< orphan*/  inode_detach_wb (struct inode*) ; 
 int /*<<< orphan*/  inode_has_buffers (struct inode*) ; 
 int /*<<< orphan*/  is_uncached_acl (scalar_t__) ; 
 int /*<<< orphan*/  locks_free_lock_context (struct inode*) ; 
 int /*<<< orphan*/  nr_inodes ; 
 int /*<<< orphan*/  posix_acl_release (scalar_t__) ; 
 int /*<<< orphan*/  security_inode_free (struct inode*) ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

void __destroy_inode(struct inode *inode)
{
	BUG_ON(inode_has_buffers(inode));
	inode_detach_wb(inode);
	security_inode_free(inode);
	fsnotify_inode_delete(inode);
	locks_free_lock_context(inode);
	if (!inode->i_nlink) {
		WARN_ON(atomic_long_read(&inode->i_sb->s_remove_count) == 0);
		atomic_long_dec(&inode->i_sb->s_remove_count);
	}

#ifdef CONFIG_FS_POSIX_ACL
	if (inode->i_acl && !is_uncached_acl(inode->i_acl))
		posix_acl_release(inode->i_acl);
	if (inode->i_default_acl && !is_uncached_acl(inode->i_default_acl))
		posix_acl_release(inode->i_default_acl);
#endif
	this_cpu_dec(nr_inodes);
}