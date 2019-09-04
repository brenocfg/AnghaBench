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
struct super_block {int /*<<< orphan*/  s_id; } ;
struct ext4_sb_info {scalar_t__ s_proc; int /*<<< orphan*/  s_kobj_unregister; int /*<<< orphan*/  s_kobj; } ;

/* Variables and functions */
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  ext4_mb_seq_groups_ops ; 
 scalar_t__ ext4_proc_root ; 
 int /*<<< orphan*/  ext4_root ; 
 int /*<<< orphan*/  ext4_sb_ktype ; 
 int /*<<< orphan*/  ext4_seq_es_shrinker_info_show ; 
 int /*<<< orphan*/  ext4_seq_options_show ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_create_seq_data (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct super_block*) ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct super_block*) ; 
 scalar_t__ proc_mkdir (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int ext4_register_sysfs(struct super_block *sb)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	int err;

	init_completion(&sbi->s_kobj_unregister);
	err = kobject_init_and_add(&sbi->s_kobj, &ext4_sb_ktype, ext4_root,
				   "%s", sb->s_id);
	if (err) {
		kobject_put(&sbi->s_kobj);
		wait_for_completion(&sbi->s_kobj_unregister);
		return err;
	}

	if (ext4_proc_root)
		sbi->s_proc = proc_mkdir(sb->s_id, ext4_proc_root);
	if (sbi->s_proc) {
		proc_create_single_data("options", S_IRUGO, sbi->s_proc,
				ext4_seq_options_show, sb);
		proc_create_single_data("es_shrinker_info", S_IRUGO,
				sbi->s_proc, ext4_seq_es_shrinker_info_show,
				sb);
		proc_create_seq_data("mb_groups", S_IRUGO, sbi->s_proc,
				&ext4_mb_seq_groups_ops, sb);
	}
	return 0;
}