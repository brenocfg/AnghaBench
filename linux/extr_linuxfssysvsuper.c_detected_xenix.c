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
struct xenix_super_block {int /*<<< orphan*/  s_fsize; int /*<<< orphan*/  s_isize; int /*<<< orphan*/  s_time; int /*<<< orphan*/  s_tfree; int /*<<< orphan*/ * s_free; int /*<<< orphan*/  s_nfree; int /*<<< orphan*/  s_tinode; int /*<<< orphan*/ * s_inode; int /*<<< orphan*/  s_ninode; } ;
struct sysv_sb_info {char* s_sbd1; char* s_sbd2; int /*<<< orphan*/  s_nzones; int /*<<< orphan*/  s_firstdatazone; int /*<<< orphan*/ * s_sb_time; int /*<<< orphan*/ * s_free_blocks; int /*<<< orphan*/ * s_bcache; int /*<<< orphan*/ * s_bcache_count; int /*<<< orphan*/ * s_sb_total_free_inodes; int /*<<< orphan*/ * s_sb_fic_inodes; int /*<<< orphan*/ * s_sb_fic_count; int /*<<< orphan*/  s_flc_size; int /*<<< orphan*/  s_fic_size; struct buffer_head* s_bh2; struct buffer_head* s_bh1; } ;
struct buffer_head {int b_data; } ;

/* Variables and functions */
 unsigned int XENIX_LINK_MAX ; 
 int /*<<< orphan*/  XENIX_NICFREE ; 
 int /*<<< orphan*/  XENIX_NICINOD ; 
 int /*<<< orphan*/  fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void detected_xenix(struct sysv_sb_info *sbi, unsigned *max_links)
{
	struct buffer_head *bh1 = sbi->s_bh1;
	struct buffer_head *bh2 = sbi->s_bh2;
	struct xenix_super_block * sbd1;
	struct xenix_super_block * sbd2;

	if (bh1 != bh2)
		sbd1 = sbd2 = (struct xenix_super_block *) bh1->b_data;
	else {
		/* block size = 512, so bh1 != bh2 */
		sbd1 = (struct xenix_super_block *) bh1->b_data;
		sbd2 = (struct xenix_super_block *) (bh2->b_data - 512);
	}

	*max_links = XENIX_LINK_MAX;
	sbi->s_fic_size = XENIX_NICINOD;
	sbi->s_flc_size = XENIX_NICFREE;
	sbi->s_sbd1 = (char *)sbd1;
	sbi->s_sbd2 = (char *)sbd2;
	sbi->s_sb_fic_count = &sbd1->s_ninode;
	sbi->s_sb_fic_inodes = &sbd1->s_inode[0];
	sbi->s_sb_total_free_inodes = &sbd2->s_tinode;
	sbi->s_bcache_count = &sbd1->s_nfree;
	sbi->s_bcache = &sbd1->s_free[0];
	sbi->s_free_blocks = &sbd2->s_tfree;
	sbi->s_sb_time = &sbd2->s_time;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd1->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd1->s_fsize);
}