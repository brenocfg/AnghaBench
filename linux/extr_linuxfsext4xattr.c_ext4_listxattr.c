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
struct dentry {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext4_xattr_block_list (struct dentry*,char*,size_t) ; 
 int ext4_xattr_ibody_list (struct dentry*,char*,size_t) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

ssize_t
ext4_listxattr(struct dentry *dentry, char *buffer, size_t buffer_size)
{
	int ret, ret2;

	down_read(&EXT4_I(d_inode(dentry))->xattr_sem);
	ret = ret2 = ext4_xattr_ibody_list(dentry, buffer, buffer_size);
	if (ret < 0)
		goto errout;
	if (buffer) {
		buffer += ret;
		buffer_size -= ret;
	}
	ret = ext4_xattr_block_list(dentry, buffer, buffer_size);
	if (ret < 0)
		goto errout;
	ret += ret2;
errout:
	up_read(&EXT4_I(d_inode(dentry))->xattr_sem);
	return ret;
}