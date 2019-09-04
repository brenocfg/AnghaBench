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
typedef  scalar_t__ u32 ;
struct super_block {int s_blocksize; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

u32
affs_checksum_block(struct super_block *sb, struct buffer_head *bh)
{
	__be32 *ptr = (__be32 *)bh->b_data;
	u32 sum;
	int bsize;

	sum = 0;
	for (bsize = sb->s_blocksize / sizeof(__be32); bsize > 0; bsize--)
		sum += be32_to_cpu(*ptr++);
	return sum;
}