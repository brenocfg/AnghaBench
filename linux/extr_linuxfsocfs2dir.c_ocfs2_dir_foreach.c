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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dir_foreach_blk (struct inode*,int /*<<< orphan*/ *,struct dir_context*,int) ; 

int ocfs2_dir_foreach(struct inode *inode, struct dir_context *ctx)
{
	u64 version = inode_query_iversion(inode);
	ocfs2_dir_foreach_blk(inode, &version, ctx, true);
	return 0;
}