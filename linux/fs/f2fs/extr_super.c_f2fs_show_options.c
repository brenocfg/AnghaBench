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
struct seq_file {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_3__ {char* inject_rate; char* inject_type; } ;
struct TYPE_4__ {char* inline_xattr_size; char* active_logs; char* write_io_size_bits; scalar_t__ whint_mode; scalar_t__ alloc_mode; char* unusable_cap; scalar_t__ fsync_mode; scalar_t__ test_dummy_encryption; TYPE_1__ fault_info; int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; int /*<<< orphan*/  root_reserved_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTIVE ; 
 scalar_t__ ALLOC_MODE_DEFAULT ; 
 scalar_t__ ALLOC_MODE_REUSE ; 
 int /*<<< orphan*/  BG_GC ; 
 int /*<<< orphan*/  DATA_FLUSH ; 
 int /*<<< orphan*/  DISABLE_CHECKPOINT ; 
 int /*<<< orphan*/  DISABLE_EXT_IDENTIFY ; 
 int /*<<< orphan*/  DISABLE_ROLL_FORWARD ; 
 int /*<<< orphan*/  DISCARD ; 
 int /*<<< orphan*/  EXTENT_CACHE ; 
 scalar_t__ F2FS_IO_SIZE_BITS (struct f2fs_sb_info*) ; 
 TYPE_2__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FASTBOOT ; 
 int /*<<< orphan*/  FAULT_INJECTION ; 
 int /*<<< orphan*/  FLUSH_MERGE ; 
 int /*<<< orphan*/  FORCE_FG_GC ; 
 scalar_t__ FSYNC_MODE_NOBARRIER ; 
 scalar_t__ FSYNC_MODE_POSIX ; 
 scalar_t__ FSYNC_MODE_STRICT ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int /*<<< orphan*/  INLINE_DATA ; 
 int /*<<< orphan*/  INLINE_DENTRY ; 
 int /*<<< orphan*/  INLINE_XATTR ; 
 int /*<<< orphan*/  INLINE_XATTR_SIZE ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  NOBARRIER ; 
 int /*<<< orphan*/  NOHEAP ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int /*<<< orphan*/  PRJQUOTA ; 
 int /*<<< orphan*/  QUOTA ; 
 int /*<<< orphan*/  RESERVE_ROOT ; 
 int /*<<< orphan*/  USRQUOTA ; 
 scalar_t__ WHINT_MODE_FS ; 
 scalar_t__ WHINT_MODE_USER ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int /*<<< orphan*/  f2fs_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_show_quota_options (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_show_options(struct seq_file *seq, struct dentry *root)
{
	struct f2fs_sb_info *sbi = F2FS_SB(root->d_sb);

	if (!f2fs_readonly(sbi->sb) && test_opt(sbi, BG_GC)) {
		if (test_opt(sbi, FORCE_FG_GC))
			seq_printf(seq, ",background_gc=%s", "sync");
		else
			seq_printf(seq, ",background_gc=%s", "on");
	} else {
		seq_printf(seq, ",background_gc=%s", "off");
	}
	if (test_opt(sbi, DISABLE_ROLL_FORWARD))
		seq_puts(seq, ",disable_roll_forward");
	if (test_opt(sbi, DISCARD))
		seq_puts(seq, ",discard");
	else
		seq_puts(seq, ",nodiscard");
	if (test_opt(sbi, NOHEAP))
		seq_puts(seq, ",no_heap");
	else
		seq_puts(seq, ",heap");
#ifdef CONFIG_F2FS_FS_XATTR
	if (test_opt(sbi, XATTR_USER))
		seq_puts(seq, ",user_xattr");
	else
		seq_puts(seq, ",nouser_xattr");
	if (test_opt(sbi, INLINE_XATTR))
		seq_puts(seq, ",inline_xattr");
	else
		seq_puts(seq, ",noinline_xattr");
	if (test_opt(sbi, INLINE_XATTR_SIZE))
		seq_printf(seq, ",inline_xattr_size=%u",
					F2FS_OPTION(sbi).inline_xattr_size);
#endif
#ifdef CONFIG_F2FS_FS_POSIX_ACL
	if (test_opt(sbi, POSIX_ACL))
		seq_puts(seq, ",acl");
	else
		seq_puts(seq, ",noacl");
#endif
	if (test_opt(sbi, DISABLE_EXT_IDENTIFY))
		seq_puts(seq, ",disable_ext_identify");
	if (test_opt(sbi, INLINE_DATA))
		seq_puts(seq, ",inline_data");
	else
		seq_puts(seq, ",noinline_data");
	if (test_opt(sbi, INLINE_DENTRY))
		seq_puts(seq, ",inline_dentry");
	else
		seq_puts(seq, ",noinline_dentry");
	if (!f2fs_readonly(sbi->sb) && test_opt(sbi, FLUSH_MERGE))
		seq_puts(seq, ",flush_merge");
	if (test_opt(sbi, NOBARRIER))
		seq_puts(seq, ",nobarrier");
	if (test_opt(sbi, FASTBOOT))
		seq_puts(seq, ",fastboot");
	if (test_opt(sbi, EXTENT_CACHE))
		seq_puts(seq, ",extent_cache");
	else
		seq_puts(seq, ",noextent_cache");
	if (test_opt(sbi, DATA_FLUSH))
		seq_puts(seq, ",data_flush");

	seq_puts(seq, ",mode=");
	if (test_opt(sbi, ADAPTIVE))
		seq_puts(seq, "adaptive");
	else if (test_opt(sbi, LFS))
		seq_puts(seq, "lfs");
	seq_printf(seq, ",active_logs=%u", F2FS_OPTION(sbi).active_logs);
	if (test_opt(sbi, RESERVE_ROOT))
		seq_printf(seq, ",reserve_root=%u,resuid=%u,resgid=%u",
				F2FS_OPTION(sbi).root_reserved_blocks,
				from_kuid_munged(&init_user_ns,
					F2FS_OPTION(sbi).s_resuid),
				from_kgid_munged(&init_user_ns,
					F2FS_OPTION(sbi).s_resgid));
	if (F2FS_IO_SIZE_BITS(sbi))
		seq_printf(seq, ",io_bits=%u",
				F2FS_OPTION(sbi).write_io_size_bits);
#ifdef CONFIG_F2FS_FAULT_INJECTION
	if (test_opt(sbi, FAULT_INJECTION)) {
		seq_printf(seq, ",fault_injection=%u",
				F2FS_OPTION(sbi).fault_info.inject_rate);
		seq_printf(seq, ",fault_type=%u",
				F2FS_OPTION(sbi).fault_info.inject_type);
	}
#endif
#ifdef CONFIG_QUOTA
	if (test_opt(sbi, QUOTA))
		seq_puts(seq, ",quota");
	if (test_opt(sbi, USRQUOTA))
		seq_puts(seq, ",usrquota");
	if (test_opt(sbi, GRPQUOTA))
		seq_puts(seq, ",grpquota");
	if (test_opt(sbi, PRJQUOTA))
		seq_puts(seq, ",prjquota");
#endif
	f2fs_show_quota_options(seq, sbi->sb);
	if (F2FS_OPTION(sbi).whint_mode == WHINT_MODE_USER)
		seq_printf(seq, ",whint_mode=%s", "user-based");
	else if (F2FS_OPTION(sbi).whint_mode == WHINT_MODE_FS)
		seq_printf(seq, ",whint_mode=%s", "fs-based");
#ifdef CONFIG_FS_ENCRYPTION
	if (F2FS_OPTION(sbi).test_dummy_encryption)
		seq_puts(seq, ",test_dummy_encryption");
#endif

	if (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_DEFAULT)
		seq_printf(seq, ",alloc_mode=%s", "default");
	else if (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_REUSE)
		seq_printf(seq, ",alloc_mode=%s", "reuse");

	if (test_opt(sbi, DISABLE_CHECKPOINT))
		seq_printf(seq, ",checkpoint=disable:%u",
				F2FS_OPTION(sbi).unusable_cap);
	if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_POSIX)
		seq_printf(seq, ",fsync_mode=%s", "posix");
	else if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT)
		seq_printf(seq, ",fsync_mode=%s", "strict");
	else if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_NOBARRIER)
		seq_printf(seq, ",fsync_mode=%s", "nobarrier");
	return 0;
}