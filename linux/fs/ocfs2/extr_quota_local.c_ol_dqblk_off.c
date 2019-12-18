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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int ol_dqblk_block (struct super_block*,int,int) ; 
 scalar_t__ ol_dqblk_block_off (struct super_block*,int,int) ; 

__attribute__((used)) static loff_t ol_dqblk_off(struct super_block *sb, int c, int off)
{
	return (ol_dqblk_block(sb, c, off) << sb->s_blocksize_bits) +
	       ol_dqblk_block_off(sb, c, off);
}