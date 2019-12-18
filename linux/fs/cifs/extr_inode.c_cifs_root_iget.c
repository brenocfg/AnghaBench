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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; } ;
struct cifs_tcon {int unix_ext; scalar_t__ pipe; int /*<<< orphan*/  resource_id; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; scalar_t__ prepath; } ;
struct TYPE_2__ {int /*<<< orphan*/  uniqueid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_DIR_SEP (struct cifs_sb_info*) ; 
 TYPE_1__* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_USE_PREFIX_PATH ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 long ENOMEM ; 
 long EOPNOTSUPP ; 
 struct inode* ERR_PTR (long) ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 long cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,struct super_block*,unsigned int,int /*<<< orphan*/ *) ; 
 long cifs_get_inode_info_unix (struct inode**,char*,struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  cifs_ipc_inode_ops ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  convert_delimiter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int strlen (scalar_t__) ; 

struct inode *cifs_root_iget(struct super_block *sb)
{
	unsigned int xid;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	struct inode *inode = NULL;
	long rc;
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	char *path = NULL;
	int len;

	if ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
	    && cifs_sb->prepath) {
		len = strlen(cifs_sb->prepath);
		path = kzalloc(len + 2 /* leading sep + null */, GFP_KERNEL);
		if (path == NULL)
			return ERR_PTR(-ENOMEM);
		path[0] = '/';
		memcpy(path+1, cifs_sb->prepath, len);
	} else {
		path = kstrdup("", GFP_KERNEL);
		if (path == NULL)
			return ERR_PTR(-ENOMEM);
	}

	xid = get_xid();
	if (tcon->unix_ext) {
		rc = cifs_get_inode_info_unix(&inode, path, sb, xid);
		/* some servers mistakenly claim POSIX support */
		if (rc != -EOPNOTSUPP)
			goto iget_no_retry;
		cifs_dbg(VFS, "server does not support POSIX extensions");
		tcon->unix_ext = false;
	}

	convert_delimiter(path, CIFS_DIR_SEP(cifs_sb));
	rc = cifs_get_inode_info(&inode, path, NULL, sb, xid, NULL);

iget_no_retry:
	if (!inode) {
		inode = ERR_PTR(rc);
		goto out;
	}

#ifdef CONFIG_CIFS_FSCACHE
	/* populate tcon->resource_id */
	tcon->resource_id = CIFS_I(inode)->uniqueid;
#endif

	if (rc && tcon->pipe) {
		cifs_dbg(FYI, "ipc connection - fake read inode\n");
		spin_lock(&inode->i_lock);
		inode->i_mode |= S_IFDIR;
		set_nlink(inode, 2);
		inode->i_op = &cifs_ipc_inode_ops;
		inode->i_fop = &simple_dir_operations;
		inode->i_uid = cifs_sb->mnt_uid;
		inode->i_gid = cifs_sb->mnt_gid;
		spin_unlock(&inode->i_lock);
	} else if (rc) {
		iget_failed(inode);
		inode = ERR_PTR(rc);
	}

out:
	kfree(path);
	free_xid(xid);
	return inode;
}