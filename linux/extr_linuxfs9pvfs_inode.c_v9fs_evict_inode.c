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
struct v9fs_inode {int /*<<< orphan*/ * writeback_fid; } ;
struct inode {int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_client_clunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_inode_put_cookie (struct inode*) ; 

void v9fs_evict_inode(struct inode *inode)
{
	struct v9fs_inode *v9inode = V9FS_I(inode);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	filemap_fdatawrite(&inode->i_data);

	v9fs_cache_inode_put_cookie(inode);
	/* clunk the fid stashed in writeback_fid */
	if (v9inode->writeback_fid) {
		p9_client_clunk(v9inode->writeback_fid);
		v9inode->writeback_fid = NULL;
	}
}