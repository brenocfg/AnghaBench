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
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ocfs2_clear_bit ; 
 int _ocfs2_free_clusters (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

int ocfs2_release_clusters(handle_t *handle,
			   struct inode *bitmap_inode,
			   struct buffer_head *bitmap_bh,
			   u64 start_blk,
			   unsigned int num_clusters)
{
	return _ocfs2_free_clusters(handle, bitmap_inode, bitmap_bh,
				    start_blk, num_clusters,
				    _ocfs2_clear_bit);
}