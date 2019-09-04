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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ page_offset (struct page*) ; 

__attribute__((used)) static int ocfs2_should_read_blk(struct inode *inode, struct page *page,
				 unsigned int block_start)
{
	u64 offset = page_offset(page) + block_start;

	if (ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)))
		return 1;

	if (i_size_read(inode) > offset)
		return 1;

	return 0;
}