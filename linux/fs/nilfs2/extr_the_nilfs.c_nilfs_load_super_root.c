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
struct the_nilfs {unsigned int ns_inode_size; int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_nongc_ctime; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_sem; struct nilfs_super_block** ns_sbp; } ;
struct super_block {int dummy; } ;
struct nilfs_super_root {int /*<<< orphan*/  sr_nongc_ctime; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_segment_usage_size; int /*<<< orphan*/  s_checkpoint_size; int /*<<< orphan*/  s_dat_entry_size; } ;
struct nilfs_inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int NILFS_SR_CPFILE_OFFSET (unsigned int) ; 
 int NILFS_SR_DAT_OFFSET (unsigned int) ; 
 int NILFS_SR_SUFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int nilfs_cpfile_read (struct super_block*,unsigned int,struct nilfs_inode*,int /*<<< orphan*/ *) ; 
 int nilfs_dat_read (struct super_block*,unsigned int,struct nilfs_inode*,int /*<<< orphan*/ *) ; 
 int nilfs_read_super_root_block (struct the_nilfs*,int /*<<< orphan*/ ,struct buffer_head**,int) ; 
 int nilfs_sufile_read (struct super_block*,unsigned int,struct nilfs_inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_load_super_root(struct the_nilfs *nilfs,
				 struct super_block *sb, sector_t sr_block)
{
	struct buffer_head *bh_sr;
	struct nilfs_super_root *raw_sr;
	struct nilfs_super_block **sbp = nilfs->ns_sbp;
	struct nilfs_inode *rawi;
	unsigned int dat_entry_size, segment_usage_size, checkpoint_size;
	unsigned int inode_size;
	int err;

	err = nilfs_read_super_root_block(nilfs, sr_block, &bh_sr, 1);
	if (unlikely(err))
		return err;

	down_read(&nilfs->ns_sem);
	dat_entry_size = le16_to_cpu(sbp[0]->s_dat_entry_size);
	checkpoint_size = le16_to_cpu(sbp[0]->s_checkpoint_size);
	segment_usage_size = le16_to_cpu(sbp[0]->s_segment_usage_size);
	up_read(&nilfs->ns_sem);

	inode_size = nilfs->ns_inode_size;

	rawi = (void *)bh_sr->b_data + NILFS_SR_DAT_OFFSET(inode_size);
	err = nilfs_dat_read(sb, dat_entry_size, rawi, &nilfs->ns_dat);
	if (err)
		goto failed;

	rawi = (void *)bh_sr->b_data + NILFS_SR_CPFILE_OFFSET(inode_size);
	err = nilfs_cpfile_read(sb, checkpoint_size, rawi, &nilfs->ns_cpfile);
	if (err)
		goto failed_dat;

	rawi = (void *)bh_sr->b_data + NILFS_SR_SUFILE_OFFSET(inode_size);
	err = nilfs_sufile_read(sb, segment_usage_size, rawi,
				&nilfs->ns_sufile);
	if (err)
		goto failed_cpfile;

	raw_sr = (struct nilfs_super_root *)bh_sr->b_data;
	nilfs->ns_nongc_ctime = le64_to_cpu(raw_sr->sr_nongc_ctime);

 failed:
	brelse(bh_sr);
	return err;

 failed_cpfile:
	iput(nilfs->ns_cpfile);

 failed_dat:
	iput(nilfs->ns_dat);
	goto failed;
}