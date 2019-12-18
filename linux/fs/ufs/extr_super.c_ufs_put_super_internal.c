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
struct ufs_sb_private_info {unsigned int s_cssize; unsigned int s_fsize; unsigned int s_fshift; unsigned int s_fpb; unsigned int s_bsize; unsigned int s_ncg; scalar_t__ s_csaddr; } ;
struct ufs_sb_info {unsigned int s_cg_loaded; unsigned char** s_ucpi; unsigned char* s_ucg; scalar_t__ s_csp; struct ufs_sb_private_info* s_uspi; } ;
struct ufs_buffer_head {int dummy; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFSD (char*) ; 
 unsigned int UFS_MAX_GROUP_LOADED ; 
 struct ufs_sb_info* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (unsigned char) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 struct ufs_buffer_head* ubh_bread (struct super_block*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  ubh_brelse (struct ufs_buffer_head*) ; 
 int /*<<< orphan*/  ubh_mark_buffer_dirty (struct ufs_buffer_head*) ; 
 int /*<<< orphan*/  ubh_mark_buffer_uptodate (struct ufs_buffer_head*,int) ; 
 int /*<<< orphan*/  ubh_memcpyubh (struct ufs_buffer_head*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  ufs_put_cstotal (struct super_block*) ; 
 int /*<<< orphan*/  ufs_put_cylinder (struct super_block*,unsigned int) ; 

__attribute__((used)) static void ufs_put_super_internal(struct super_block *sb)
{
	struct ufs_sb_info *sbi = UFS_SB(sb);
	struct ufs_sb_private_info *uspi = sbi->s_uspi;
	struct ufs_buffer_head * ubh;
	unsigned char * base, * space;
	unsigned blks, size, i;

	
	UFSD("ENTER\n");

	ufs_put_cstotal(sb);
	size = uspi->s_cssize;
	blks = (size + uspi->s_fsize - 1) >> uspi->s_fshift;
	base = space = (char*) sbi->s_csp;
	for (i = 0; i < blks; i += uspi->s_fpb) {
		size = uspi->s_bsize;
		if (i + uspi->s_fpb > blks)
			size = (blks - i) * uspi->s_fsize;

		ubh = ubh_bread(sb, uspi->s_csaddr + i, size);

		ubh_memcpyubh (ubh, space, size);
		space += size;
		ubh_mark_buffer_uptodate (ubh, 1);
		ubh_mark_buffer_dirty (ubh);
		ubh_brelse (ubh);
	}
	for (i = 0; i < sbi->s_cg_loaded; i++) {
		ufs_put_cylinder (sb, i);
		kfree (sbi->s_ucpi[i]);
	}
	for (; i < UFS_MAX_GROUP_LOADED; i++) 
		kfree (sbi->s_ucpi[i]);
	for (i = 0; i < uspi->s_ncg; i++) 
		brelse (sbi->s_ucg[i]);
	kfree (sbi->s_ucg);
	kfree (base);

	UFSD("EXIT\n");
}