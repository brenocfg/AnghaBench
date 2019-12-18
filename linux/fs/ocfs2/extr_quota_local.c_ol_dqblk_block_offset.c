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
struct super_block {int s_blocksize_bits; } ;
typedef  int loff_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ol_dqblk_block_offset(struct super_block *sb, loff_t off)
{
	return off & ((1 << sb->s_blocksize_bits) - 1);
}