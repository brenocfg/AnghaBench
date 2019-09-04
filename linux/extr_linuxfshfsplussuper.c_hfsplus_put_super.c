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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct hfsplus_vh {int /*<<< orphan*/  attributes; int /*<<< orphan*/  modify_date; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  nls; int /*<<< orphan*/ * s_backup_vhdr_buf; int /*<<< orphan*/ * s_vhdr_buf; int /*<<< orphan*/  hidden_dir; int /*<<< orphan*/  alloc_file; int /*<<< orphan*/  ext_tree; int /*<<< orphan*/  cat_tree; int /*<<< orphan*/  attr_tree; struct hfsplus_vh* s_vhdr; int /*<<< orphan*/  sync_work; } ;

/* Variables and functions */
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFSPLUS_VOL_INCNSTNT ; 
 int /*<<< orphan*/  HFSPLUS_VOL_UNMNT ; 
 int /*<<< orphan*/  SUPER ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_btree_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfsp_now2mt () ; 
 int /*<<< orphan*/  hfsplus_sync_fs (struct super_block*,int) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfsplus_put_super(struct super_block *sb)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);

	hfs_dbg(SUPER, "hfsplus_put_super\n");

	cancel_delayed_work_sync(&sbi->sync_work);

	if (!sb_rdonly(sb) && sbi->s_vhdr) {
		struct hfsplus_vh *vhdr = sbi->s_vhdr;

		vhdr->modify_date = hfsp_now2mt();
		vhdr->attributes |= cpu_to_be32(HFSPLUS_VOL_UNMNT);
		vhdr->attributes &= cpu_to_be32(~HFSPLUS_VOL_INCNSTNT);

		hfsplus_sync_fs(sb, 1);
	}

	hfs_btree_close(sbi->attr_tree);
	hfs_btree_close(sbi->cat_tree);
	hfs_btree_close(sbi->ext_tree);
	iput(sbi->alloc_file);
	iput(sbi->hidden_dir);
	kfree(sbi->s_vhdr_buf);
	kfree(sbi->s_backup_vhdr_buf);
	unload_nls(sbi->nls);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;
}