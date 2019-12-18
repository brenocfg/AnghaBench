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
struct inode {int dummy; } ;
struct getxattr_iter {int buffer_size; int /*<<< orphan*/  it; } ;

/* Variables and functions */
 int ENOATTR ; 
 int /*<<< orphan*/  find_xattr_handlers ; 
 int inline_xattr_iter_begin (int /*<<< orphan*/ *,struct inode*) ; 
 int xattr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  xattr_iter_end_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inline_getxattr(struct inode *inode, struct getxattr_iter *it)
{
	int ret;
	unsigned int remaining;

	ret = inline_xattr_iter_begin(&it->it, inode);
	if (ret < 0)
		return ret;

	remaining = ret;
	while (remaining) {
		ret = xattr_foreach(&it->it, &find_xattr_handlers, &remaining);
		if (ret != -ENOATTR)
			break;
	}
	xattr_iter_end_final(&it->it);

	return ret ? ret : it->buffer_size;
}