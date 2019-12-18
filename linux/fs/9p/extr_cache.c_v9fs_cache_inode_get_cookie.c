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
struct v9fs_session_info {int /*<<< orphan*/  fscache; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  path; } ;
struct v9fs_inode {scalar_t__ fscache; int /*<<< orphan*/  vfs_inode; TYPE_1__ qid; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 scalar_t__ fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,struct v9fs_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  v9fs_cache_inode_index_def ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

void v9fs_cache_inode_get_cookie(struct inode *inode)
{
	struct v9fs_inode *v9inode;
	struct v9fs_session_info *v9ses;

	if (!S_ISREG(inode->i_mode))
		return;

	v9inode = V9FS_I(inode);
	if (v9inode->fscache)
		return;

	v9ses = v9fs_inode2v9ses(inode);
	v9inode->fscache = fscache_acquire_cookie(v9ses->fscache,
						  &v9fs_cache_inode_index_def,
						  &v9inode->qid.path,
						  sizeof(v9inode->qid.path),
						  &v9inode->qid.version,
						  sizeof(v9inode->qid.version),
						  v9inode,
						  i_size_read(&v9inode->vfs_inode),
						  true);

	p9_debug(P9_DEBUG_FSC, "inode %p get cookie %p\n",
		 inode, v9inode->fscache);
}