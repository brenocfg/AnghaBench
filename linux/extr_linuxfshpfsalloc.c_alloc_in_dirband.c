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
struct super_block {int dummy; } ;
struct hpfs_sb_info {unsigned int sb_dirband_start; unsigned int sb_dirband_size; } ;
typedef  int secno ;

/* Variables and functions */
 int alloc_in_bmp (struct super_block*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_claim_dirband_alloc (struct super_block*,int) ; 
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 

__attribute__((used)) static secno alloc_in_dirband(struct super_block *s, secno near)
{
	unsigned nr = near;
	secno sec;
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	if (nr < sbi->sb_dirband_start)
		nr = sbi->sb_dirband_start;
	if (nr >= sbi->sb_dirband_start + sbi->sb_dirband_size)
		nr = sbi->sb_dirband_start + sbi->sb_dirband_size - 4;
	nr -= sbi->sb_dirband_start;
	nr >>= 2;
	sec = alloc_in_bmp(s, (~0x3fff) | nr, 1, 0);
	if (!sec) return 0;
	hpfs_claim_dirband_alloc(s, sec);
	return ((sec & 0x3fff) << 2) + sbi->sb_dirband_start;
}