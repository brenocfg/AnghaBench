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
struct v9fs_inode {int /*<<< orphan*/  cache_validity; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  V9FS_INO_INVALID_ATTR ; 

__attribute__((used)) static inline void v9fs_invalidate_inode_attr(struct inode *inode)
{
	struct v9fs_inode *v9inode;
	v9inode = V9FS_I(inode);
	v9inode->cache_validity |= V9FS_INO_INVALID_ATTR;
	return;
}