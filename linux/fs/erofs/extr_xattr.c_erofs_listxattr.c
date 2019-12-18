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
struct TYPE_2__ {int /*<<< orphan*/  sb; } ;
struct listxattr_iter {char* buffer; size_t buffer_size; TYPE_1__ it; scalar_t__ buffer_ofs; struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOATTR ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int init_inode_xattrs (int /*<<< orphan*/ ) ; 
 int inline_listxattr (struct listxattr_iter*) ; 
 int shared_listxattr (struct listxattr_iter*) ; 

ssize_t erofs_listxattr(struct dentry *dentry,
			char *buffer, size_t buffer_size)
{
	int ret;
	struct listxattr_iter it;

	ret = init_inode_xattrs(d_inode(dentry));
	if (ret)
		return ret;

	it.dentry = dentry;
	it.buffer = buffer;
	it.buffer_size = buffer_size;
	it.buffer_ofs = 0;

	it.it.sb = dentry->d_sb;

	ret = inline_listxattr(&it);
	if (ret < 0 && ret != -ENOATTR)
		return ret;
	return shared_listxattr(&it);
}