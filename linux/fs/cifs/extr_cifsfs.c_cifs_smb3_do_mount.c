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
struct super_block {int /*<<< orphan*/  local_nls; int /*<<< orphan*/  s_flags; scalar_t__ s_root; } ;
struct smb_vol {int /*<<< orphan*/  local_nls; int /*<<< orphan*/  s_flags; scalar_t__ s_root; } ;
struct file_system_type {int dummy; } ;
struct dentry {int /*<<< orphan*/  local_nls; int /*<<< orphan*/  s_flags; scalar_t__ s_root; } ;
struct cifs_sb_info {struct cifs_sb_info* mountdata; struct cifs_sb_info* prepath; } ;
struct cifs_mnt_data {int flags; struct cifs_sb_info* cifs_sb; struct super_block* vol; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct super_block* ERR_CAST (struct super_block*) ; 
 struct super_block* ERR_PTR (int) ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int SB_NOATIME ; 
 int SB_NODIRATIME ; 
 int SB_SILENT ; 
 int /*<<< orphan*/  VFS ; 
 scalar_t__ cifsFYI ; 
 int /*<<< orphan*/  cifs_cleanup_volume_info (struct super_block*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct super_block* cifs_get_root (struct super_block*,struct super_block*) ; 
 struct super_block* cifs_get_volume_info (char*,char const*,int) ; 
 int /*<<< orphan*/  cifs_info (char*,char const*) ; 
 int /*<<< orphan*/  cifs_match_super ; 
 int cifs_mount (struct cifs_sb_info*,struct super_block*) ; 
 int cifs_read_super (struct super_block*) ; 
 int /*<<< orphan*/  cifs_set_super ; 
 int cifs_setup_cifs_sb (struct super_block*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_umount (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct cifs_sb_info*) ; 
 struct cifs_sb_info* kstrndup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cifs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cifs_mnt_data*) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *
cifs_smb3_do_mount(struct file_system_type *fs_type,
	      int flags, const char *dev_name, void *data, bool is_smb3)
{
	int rc;
	struct super_block *sb;
	struct cifs_sb_info *cifs_sb;
	struct smb_vol *volume_info;
	struct cifs_mnt_data mnt_data;
	struct dentry *root;

	/*
	 * Prints in Kernel / CIFS log the attempted mount operation
	 *	If CIFS_DEBUG && cifs_FYI
	 */
	if (cifsFYI)
		cifs_dbg(FYI, "Devname: %s flags: %d\n", dev_name, flags);
	else
		cifs_info("Attempting to mount %s\n", dev_name);

	volume_info = cifs_get_volume_info((char *)data, dev_name, is_smb3);
	if (IS_ERR(volume_info))
		return ERR_CAST(volume_info);

	cifs_sb = kzalloc(sizeof(struct cifs_sb_info), GFP_KERNEL);
	if (cifs_sb == NULL) {
		root = ERR_PTR(-ENOMEM);
		goto out_nls;
	}

	cifs_sb->mountdata = kstrndup(data, PAGE_SIZE, GFP_KERNEL);
	if (cifs_sb->mountdata == NULL) {
		root = ERR_PTR(-ENOMEM);
		goto out_free;
	}

	rc = cifs_setup_cifs_sb(volume_info, cifs_sb);
	if (rc) {
		root = ERR_PTR(rc);
		goto out_free;
	}

	rc = cifs_mount(cifs_sb, volume_info);
	if (rc) {
		if (!(flags & SB_SILENT))
			cifs_dbg(VFS, "cifs_mount failed w/return code = %d\n",
				 rc);
		root = ERR_PTR(rc);
		goto out_free;
	}

	mnt_data.vol = volume_info;
	mnt_data.cifs_sb = cifs_sb;
	mnt_data.flags = flags;

	/* BB should we make this contingent on mount parm? */
	flags |= SB_NODIRATIME | SB_NOATIME;

	sb = sget(fs_type, cifs_match_super, cifs_set_super, flags, &mnt_data);
	if (IS_ERR(sb)) {
		root = ERR_CAST(sb);
		cifs_umount(cifs_sb);
		goto out;
	}

	if (sb->s_root) {
		cifs_dbg(FYI, "Use existing superblock\n");
		cifs_umount(cifs_sb);
	} else {
		rc = cifs_read_super(sb);
		if (rc) {
			root = ERR_PTR(rc);
			goto out_super;
		}

		sb->s_flags |= SB_ACTIVE;
	}

	root = cifs_get_root(volume_info, sb);
	if (IS_ERR(root))
		goto out_super;

	cifs_dbg(FYI, "dentry root is: %p\n", root);
	goto out;

out_super:
	deactivate_locked_super(sb);
out:
	cifs_cleanup_volume_info(volume_info);
	return root;

out_free:
	kfree(cifs_sb->prepath);
	kfree(cifs_sb->mountdata);
	kfree(cifs_sb);
out_nls:
	unload_nls(volume_info->local_nls);
	goto out;
}