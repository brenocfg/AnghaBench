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
struct TYPE_3__ {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {int ro_mount; TYPE_1__ vi; } ;
struct ubi_volume_desc {scalar_t__ s_root; int /*<<< orphan*/  s_flags; struct ubifs_info* s_fs_info; } ;
struct super_block {scalar_t__ s_root; int /*<<< orphan*/  s_flags; struct ubifs_info* s_fs_info; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_UBIFS_ATIME_SUPPORT ; 
 int EBUSY ; 
 int ENOMEM ; 
 struct dentry* ERR_CAST (struct ubi_volume_desc*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ubi_volume_desc*) ; 
 int PTR_ERR (struct ubi_volume_desc*) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  SB_NOATIME ; 
 int SB_RDONLY ; 
 int SB_SILENT ; 
 int /*<<< orphan*/  UBI_READONLY ; 
 struct ubifs_info* alloc_ubifs_info (struct ubi_volume_desc*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct ubi_volume_desc*) ; 
 struct dentry* dget (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ubifs_info*) ; 
 struct ubi_volume_desc* open_ubi (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sb_set ; 
 int /*<<< orphan*/  sb_test ; 
 struct ubi_volume_desc* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ubifs_info*) ; 
 int /*<<< orphan*/  ubi_close_volume (struct ubi_volume_desc*) ; 
 int ubifs_fill_super (struct ubi_volume_desc*,void*,int) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*) ; 

__attribute__((used)) static struct dentry *ubifs_mount(struct file_system_type *fs_type, int flags,
			const char *name, void *data)
{
	struct ubi_volume_desc *ubi;
	struct ubifs_info *c;
	struct super_block *sb;
	int err;

	dbg_gen("name %s, flags %#x", name, flags);

	/*
	 * Get UBI device number and volume ID. Mount it read-only so far
	 * because this might be a new mount point, and UBI allows only one
	 * read-write user at a time.
	 */
	ubi = open_ubi(name, UBI_READONLY);
	if (IS_ERR(ubi)) {
		if (!(flags & SB_SILENT))
			pr_err("UBIFS error (pid: %d): cannot open \"%s\", error %d",
			       current->pid, name, (int)PTR_ERR(ubi));
		return ERR_CAST(ubi);
	}

	c = alloc_ubifs_info(ubi);
	if (!c) {
		err = -ENOMEM;
		goto out_close;
	}

	dbg_gen("opened ubi%d_%d", c->vi.ubi_num, c->vi.vol_id);

	sb = sget(fs_type, sb_test, sb_set, flags, c);
	if (IS_ERR(sb)) {
		err = PTR_ERR(sb);
		kfree(c);
		goto out_close;
	}

	if (sb->s_root) {
		struct ubifs_info *c1 = sb->s_fs_info;
		kfree(c);
		/* A new mount point for already mounted UBIFS */
		dbg_gen("this ubi volume is already mounted");
		if (!!(flags & SB_RDONLY) != c1->ro_mount) {
			err = -EBUSY;
			goto out_deact;
		}
	} else {
		err = ubifs_fill_super(sb, data, flags & SB_SILENT ? 1 : 0);
		if (err) {
			kfree(c);
			goto out_deact;
		}
		/* We do not support atime */
		sb->s_flags |= SB_ACTIVE;
		if (IS_ENABLED(CONFIG_UBIFS_ATIME_SUPPORT))
			ubifs_msg(c, "full atime support is enabled.");
		else
			sb->s_flags |= SB_NOATIME;
	}

	/* 'fill_super()' opens ubi again so we must close it here */
	ubi_close_volume(ubi);

	return dget(sb->s_root);

out_deact:
	deactivate_locked_super(sb);
out_close:
	ubi_close_volume(ubi);
	return ERR_PTR(err);
}