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
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct cifs_tcon {scalar_t__ unix_ext; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;

/* Variables and functions */
 int CIFSUnixCreateSymLink (unsigned int,struct cifs_tcon*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int cifs_get_inode_info_unix (struct inode**,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_remap (struct cifs_sb_info*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int create_mf_symlink (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*,char const*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int
cifs_symlink(struct inode *inode, struct dentry *direntry, const char *symname)
{
	int rc = -EOPNOTSUPP;
	unsigned int xid;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	char *full_path = NULL;
	struct inode *newinode = NULL;

	xid = get_xid();

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		rc = PTR_ERR(tlink);
		goto symlink_exit;
	}
	pTcon = tlink_tcon(tlink);

	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto symlink_exit;
	}

	cifs_dbg(FYI, "Full path: %s\n", full_path);
	cifs_dbg(FYI, "symname is %s\n", symname);

	/* BB what if DFS and this volume is on different share? BB */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = create_mf_symlink(xid, pTcon, cifs_sb, full_path, symname);
	else if (pTcon->unix_ext)
		rc = CIFSUnixCreateSymLink(xid, pTcon, full_path, symname,
					   cifs_sb->local_nls,
					   cifs_remap(cifs_sb));
	/* else
	   rc = CIFSCreateReparseSymLink(xid, pTcon, fromName, toName,
					cifs_sb_target->local_nls); */

	if (rc == 0) {
		if (pTcon->unix_ext)
			rc = cifs_get_inode_info_unix(&newinode, full_path,
						      inode->i_sb, xid);
		else
			rc = cifs_get_inode_info(&newinode, full_path, NULL,
						 inode->i_sb, xid, NULL);

		if (rc != 0) {
			cifs_dbg(FYI, "Create symlink ok, getinodeinfo fail rc = %d\n",
				 rc);
		} else {
			d_instantiate(direntry, newinode);
		}
	}
symlink_exit:
	kfree(full_path);
	cifs_put_tlink(tlink);
	free_xid(xid);
	return rc;
}