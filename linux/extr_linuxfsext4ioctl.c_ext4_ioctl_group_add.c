#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct file {int dummy; } ;
struct ext4_new_group_data {int /*<<< orphan*/  group; } ;
struct TYPE_4__ {scalar_t__ s_journal; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  INIT_INODE_TABLE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int ext4_group_add (struct super_block*,struct ext4_new_group_data*) ; 
 scalar_t__ ext4_has_feature_bigalloc (struct super_block*) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int ext4_register_li_request (struct super_block*,int /*<<< orphan*/ ) ; 
 int ext4_resize_begin (struct super_block*) ; 
 int /*<<< orphan*/  ext4_resize_end (struct super_block*) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int jbd2_journal_flush (scalar_t__) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (scalar_t__) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (scalar_t__) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ext4_ioctl_group_add(struct file *file,
				 struct ext4_new_group_data *input)
{
	struct super_block *sb = file_inode(file)->i_sb;
	int err, err2=0;

	err = ext4_resize_begin(sb);
	if (err)
		return err;

	if (ext4_has_feature_bigalloc(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "Online resizing not supported with bigalloc");
		err = -EOPNOTSUPP;
		goto group_add_out;
	}

	err = mnt_want_write_file(file);
	if (err)
		goto group_add_out;

	err = ext4_group_add(sb, input);
	if (EXT4_SB(sb)->s_journal) {
		jbd2_journal_lock_updates(EXT4_SB(sb)->s_journal);
		err2 = jbd2_journal_flush(EXT4_SB(sb)->s_journal);
		jbd2_journal_unlock_updates(EXT4_SB(sb)->s_journal);
	}
	if (err == 0)
		err = err2;
	mnt_drop_write_file(file);
	if (!err && ext4_has_group_desc_csum(sb) &&
	    test_opt(sb, INIT_INODE_TABLE))
		err = ext4_register_li_request(sb, input->group);
group_add_out:
	ext4_resize_end(sb);
	return err;
}