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
 int _ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

int ocfs2_free_suballoc_bits(handle_t *handle,
			     struct inode *alloc_inode,
			     struct buffer_head *alloc_bh,
			     unsigned int start_bit,
			     u64 bg_blkno,
			     unsigned int count)
{
	return _ocfs2_free_suballoc_bits(handle, alloc_inode, alloc_bh,
					 start_bit, bg_blkno, count, NULL);
}