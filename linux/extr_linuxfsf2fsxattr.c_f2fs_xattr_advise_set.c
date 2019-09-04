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
struct xattr_handler {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {unsigned char i_advise; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 unsigned char FADVISE_MODIFIABLE_BITS ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 

__attribute__((used)) static int f2fs_xattr_advise_set(const struct xattr_handler *handler,
		struct dentry *unused, struct inode *inode,
		const char *name, const void *value,
		size_t size, int flags)
{
	unsigned char old_advise = F2FS_I(inode)->i_advise;
	unsigned char new_advise;

	if (!inode_owner_or_capable(inode))
		return -EPERM;
	if (value == NULL)
		return -EINVAL;

	new_advise = *(char *)value;
	if (new_advise & ~FADVISE_MODIFIABLE_BITS)
		return -EINVAL;

	new_advise = new_advise & FADVISE_MODIFIABLE_BITS;
	new_advise |= old_advise & ~FADVISE_MODIFIABLE_BITS;

	F2FS_I(inode)->i_advise = new_advise;
	f2fs_mark_inode_dirty_sync(inode, true);
	return 0;
}