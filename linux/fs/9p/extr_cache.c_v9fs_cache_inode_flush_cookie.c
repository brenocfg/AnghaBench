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
struct v9fs_inode {int /*<<< orphan*/ * fscache; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct inode*,int /*<<< orphan*/ *) ; 

void v9fs_cache_inode_flush_cookie(struct inode *inode)
{
	struct v9fs_inode *v9inode = V9FS_I(inode);

	if (!v9inode->fscache)
		return;
	p9_debug(P9_DEBUG_FSC, "inode %p flush cookie %p\n",
		 inode, v9inode->fscache);

	fscache_relinquish_cookie(v9inode->fscache, NULL, true);
	v9inode->fscache = NULL;
}