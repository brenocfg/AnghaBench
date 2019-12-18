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
struct super_block {int s_blocksize_bits; int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static int ocfs2_bucket_align_free_start(struct super_block *sb,
					 int free_start, int size)
{
	/*
	 * We need to make sure that the name+value pair fits within
	 * one block.
	 */
	if (((free_start - size) >> sb->s_blocksize_bits) !=
	    ((free_start - 1) >> sb->s_blocksize_bits))
		free_start -= free_start % sb->s_blocksize;

	return free_start;
}