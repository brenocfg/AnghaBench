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
struct super_block {unsigned int s_blocksize; } ;
struct ocfs2_dir_block_trailer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ocfs2_dir_trailer_blk_off(struct super_block *sb)
{
	return sb->s_blocksize - sizeof(struct ocfs2_dir_block_trailer);
}