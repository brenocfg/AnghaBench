#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct cifs_tcon {TYPE_1__* ses; scalar_t__ unix_ext; } ;
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
struct cifsInodeInfo {scalar_t__ time; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_lock; } ;
struct TYPE_7__ {int (* create_hardlink ) (unsigned int,struct cifs_tcon*,char*,char*,struct cifs_sb_info*) ;} ;
struct TYPE_6__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int CIFSUnixCreateHardLink (unsigned int,struct cifs_tcon*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cifsInodeInfo* CIFS_I (TYPE_3__*) ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_remap (struct cifs_sb_info*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 TYPE_3__* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  inc_nlink (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (unsigned int,struct cifs_tcon*,char*,char*,struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int
cifs_hardlink(struct dentry *old_file, struct inode *inode,
	      struct dentry *direntry)
{
	int rc = -EACCES;
	unsigned int xid;
	char *from_name = NULL;
	char *to_name = NULL;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink;
	struct cifs_tcon *tcon;
	struct TCP_Server_Info *server;
	struct cifsInodeInfo *cifsInode;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	xid = get_xid();

	from_name = build_path_from_dentry(old_file);
	to_name = build_path_from_dentry(direntry);
	if ((from_name == NULL) || (to_name == NULL)) {
		rc = -ENOMEM;
		goto cifs_hl_exit;
	}

	if (tcon->unix_ext)
		rc = CIFSUnixCreateHardLink(xid, tcon, from_name, to_name,
					    cifs_sb->local_nls,
					    cifs_remap(cifs_sb));
	else {
		server = tcon->ses->server;
		if (!server->ops->create_hardlink) {
			rc = -ENOSYS;
			goto cifs_hl_exit;
		}
		rc = server->ops->create_hardlink(xid, tcon, from_name, to_name,
						  cifs_sb);
		if ((rc == -EIO) || (rc == -EINVAL))
			rc = -EOPNOTSUPP;
	}

	d_drop(direntry);	/* force new lookup from server of target */

	/*
	 * if source file is cached (oplocked) revalidate will not go to server
	 * until the file is closed or oplock broken so update nlinks locally
	 */
	if (d_really_is_positive(old_file)) {
		cifsInode = CIFS_I(d_inode(old_file));
		if (rc == 0) {
			spin_lock(&d_inode(old_file)->i_lock);
			inc_nlink(d_inode(old_file));
			spin_unlock(&d_inode(old_file)->i_lock);

			/*
			 * parent dir timestamps will update from srv within a
			 * second, would it really be worth it to set the parent
			 * dir cifs inode time to zero to force revalidate
			 * (faster) for it too?
			 */
		}
		/*
		 * if not oplocked will force revalidate to get info on source
		 * file from srv.  Note Samba server prior to 4.2 has bug -
		 * not updating src file ctime on hardlinks but Windows servers
		 * handle it properly
		 */
		cifsInode->time = 0;

		/*
		 * Will update parent dir timestamps from srv within a second.
		 * Would it really be worth it to set the parent dir (cifs
		 * inode) time field to zero to force revalidate on parent
		 * directory faster ie
		 *
		 * CIFS_I(inode)->time = 0;
		 */
	}

cifs_hl_exit:
	kfree(from_name);
	kfree(to_name);
	free_xid(xid);
	cifs_put_tlink(tlink);
	return rc;
}