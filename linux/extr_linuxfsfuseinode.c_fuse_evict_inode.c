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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_data; } ;
struct fuse_inode {int /*<<< orphan*/ * forget; int /*<<< orphan*/  nlookup; int /*<<< orphan*/  nodeid; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int SB_ACTIVE ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  fuse_queue_forget (struct fuse_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_evict_inode(struct inode *inode)
{
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	if (inode->i_sb->s_flags & SB_ACTIVE) {
		struct fuse_conn *fc = get_fuse_conn(inode);
		struct fuse_inode *fi = get_fuse_inode(inode);
		fuse_queue_forget(fc, fi->forget, fi->nodeid, fi->nlookup);
		fi->forget = NULL;
	}
}