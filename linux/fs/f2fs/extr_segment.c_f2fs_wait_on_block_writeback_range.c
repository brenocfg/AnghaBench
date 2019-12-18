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
typedef  scalar_t__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  f2fs_wait_on_block_writeback (struct inode*,scalar_t__) ; 

void f2fs_wait_on_block_writeback_range(struct inode *inode, block_t blkaddr,
								block_t len)
{
	block_t i;

	for (i = 0; i < len; i++)
		f2fs_wait_on_block_writeback(inode, blkaddr + i);
}