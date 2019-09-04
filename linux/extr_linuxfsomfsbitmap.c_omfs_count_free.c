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
struct super_block {int s_blocksize; } ;
struct omfs_sb_info {unsigned int s_imap_size; int /*<<< orphan*/ * s_imap; } ;

/* Variables and functions */
 struct omfs_sb_info* OMFS_SB (struct super_block*) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 

unsigned long omfs_count_free(struct super_block *sb)
{
	unsigned int i;
	unsigned long sum = 0;
	struct omfs_sb_info *sbi = OMFS_SB(sb);
	int nbits = sb->s_blocksize * 8;

	for (i = 0; i < sbi->s_imap_size; i++)
		sum += nbits - bitmap_weight(sbi->s_imap[i], nbits);

	return sum;
}