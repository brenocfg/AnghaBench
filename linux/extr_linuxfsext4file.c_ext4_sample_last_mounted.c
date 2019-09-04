#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct super_block {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; struct vfsmount* mnt; } ;
struct ext4_sb_info {int s_mount_flags; TYPE_1__* s_es; int /*<<< orphan*/  s_sbh; } ;
typedef  char handle_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  s_last_mounted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXT4_HT_MISC ; 
 int EXT4_MF_MNTDIR_SAMPLED ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 char* d_path (struct path*,char*,int) ; 
 int /*<<< orphan*/  ext4_handle_dirty_super (char*,struct super_block*) ; 
 int ext4_journal_get_write_access (char*,int /*<<< orphan*/ ) ; 
 char* ext4_journal_start_sb (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sb_end_intwrite (struct super_block*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sb_start_intwrite_trylock (struct super_block*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ext4_sample_last_mounted(struct super_block *sb,
				    struct vfsmount *mnt)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct path path;
	char buf[64], *cp;
	handle_t *handle;
	int err;

	if (likely(sbi->s_mount_flags & EXT4_MF_MNTDIR_SAMPLED))
		return 0;

	if (sb_rdonly(sb) || !sb_start_intwrite_trylock(sb))
		return 0;

	sbi->s_mount_flags |= EXT4_MF_MNTDIR_SAMPLED;
	/*
	 * Sample where the filesystem has been mounted and
	 * store it in the superblock for sysadmin convenience
	 * when trying to sort through large numbers of block
	 * devices or filesystem images.
	 */
	memset(buf, 0, sizeof(buf));
	path.mnt = mnt;
	path.dentry = mnt->mnt_root;
	cp = d_path(&path, buf, sizeof(buf));
	err = 0;
	if (IS_ERR(cp))
		goto out;

	handle = ext4_journal_start_sb(sb, EXT4_HT_MISC, 1);
	err = PTR_ERR(handle);
	if (IS_ERR(handle))
		goto out;
	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_write_access(handle, sbi->s_sbh);
	if (err)
		goto out_journal;
	strlcpy(sbi->s_es->s_last_mounted, cp,
		sizeof(sbi->s_es->s_last_mounted));
	ext4_handle_dirty_super(handle, sb);
out_journal:
	ext4_journal_stop(handle);
out:
	sb_end_intwrite(sb);
	return err;
}