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
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* query_symlink ) (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*,char**,int) ;} ;
struct TYPE_3__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int ATTR_REPARSE ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ECHILD ; 
 int ENOMEM ; 
 char const* ERR_CAST (struct tcon_link*) ; 
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char*,struct inode*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kfree_link ; 
 int query_mf_symlink (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*,char**) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*,char**,int) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

const char *
cifs_get_link(struct dentry *direntry, struct inode *inode,
	      struct delayed_call *done)
{
	int rc = -ENOMEM;
	unsigned int xid;
	char *full_path = NULL;
	char *target_path = NULL;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *tcon;
	struct TCP_Server_Info *server;

	if (!direntry)
		return ERR_PTR(-ECHILD);

	xid = get_xid();

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		free_xid(xid);
		return ERR_CAST(tlink);
	}
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	full_path = build_path_from_dentry(direntry);
	if (!full_path) {
		free_xid(xid);
		cifs_put_tlink(tlink);
		return ERR_PTR(-ENOMEM);
	}

	cifs_dbg(FYI, "Full path: %s inode = 0x%p\n", full_path, inode);

	rc = -EACCES;
	/*
	 * First try Minshall+French Symlinks, if configured
	 * and fallback to UNIX Extensions Symlinks.
	 */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = query_mf_symlink(xid, tcon, cifs_sb, full_path,
				      &target_path);

	if (rc != 0 && server->ops->query_symlink) {
		struct cifsInodeInfo *cifsi = CIFS_I(inode);
		bool reparse_point = false;

		if (cifsi->cifsAttrs & ATTR_REPARSE)
			reparse_point = true;

		rc = server->ops->query_symlink(xid, tcon, cifs_sb, full_path,
						&target_path, reparse_point);
	}

	kfree(full_path);
	free_xid(xid);
	cifs_put_tlink(tlink);
	if (rc != 0) {
		kfree(target_path);
		return ERR_PTR(rc);
	}
	set_delayed_call(done, kfree_link, target_path);
	return target_path;
}