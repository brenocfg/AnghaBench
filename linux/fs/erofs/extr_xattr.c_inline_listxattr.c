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
struct listxattr_iter {int buffer_ofs; int /*<<< orphan*/  it; int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int inline_xattr_iter_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_xattr_handlers ; 
 int xattr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  xattr_iter_end_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inline_listxattr(struct listxattr_iter *it)
{
	int ret;
	unsigned int remaining;

	ret = inline_xattr_iter_begin(&it->it, d_inode(it->dentry));
	if (ret < 0)
		return ret;

	remaining = ret;
	while (remaining) {
		ret = xattr_foreach(&it->it, &list_xattr_handlers, &remaining);
		if (ret)
			break;
	}
	xattr_iter_end_final(&it->it);
	return ret ? ret : it->buffer_ofs;
}