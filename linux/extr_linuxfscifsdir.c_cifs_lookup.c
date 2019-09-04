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
struct dentry {int /*<<< orphan*/  i_sb; } ;
struct cifs_tcon {scalar_t__ unix_ext; } ;
struct cifs_sb_info {int dummy; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct inode* ERR_CAST (struct tcon_link*) ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct inode*) ; 
 int check_name (struct inode*,struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int cifs_get_inode_info_unix (struct inode**,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_set_time (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct inode*) ; 
 scalar_t__ d_really_is_positive (struct inode*) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  renew_parental_timestamps (struct inode*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *
cifs_lookup(struct inode *parent_dir_inode, struct dentry *direntry,
	    unsigned int flags)
{
	unsigned int xid;
	int rc = 0; /* to get around spurious gcc warning, set to zero here */
	struct cifs_sb_info *cifs_sb;
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	struct inode *newInode = NULL;
	char *full_path = NULL;

	xid = get_xid();

	cifs_dbg(FYI, "parent inode = 0x%p name is: %pd and dentry = 0x%p\n",
		 parent_dir_inode, direntry, direntry);

	/* check whether path exists */

	cifs_sb = CIFS_SB(parent_dir_inode->i_sb);
	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		free_xid(xid);
		return ERR_CAST(tlink);
	}
	pTcon = tlink_tcon(tlink);

	rc = check_name(direntry, pTcon);
	if (unlikely(rc)) {
		cifs_put_tlink(tlink);
		free_xid(xid);
		return ERR_PTR(rc);
	}

	/* can not grab the rename sem here since it would
	deadlock in the cases (beginning of sys_rename itself)
	in which we already have the sb rename sem */
	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		cifs_put_tlink(tlink);
		free_xid(xid);
		return ERR_PTR(-ENOMEM);
	}

	if (d_really_is_positive(direntry)) {
		cifs_dbg(FYI, "non-NULL inode in lookup\n");
	} else {
		cifs_dbg(FYI, "NULL inode in lookup\n");
	}
	cifs_dbg(FYI, "Full path: %s inode = 0x%p\n",
		 full_path, d_inode(direntry));

	if (pTcon->unix_ext) {
		rc = cifs_get_inode_info_unix(&newInode, full_path,
					      parent_dir_inode->i_sb, xid);
	} else {
		rc = cifs_get_inode_info(&newInode, full_path, NULL,
				parent_dir_inode->i_sb, xid, NULL);
	}

	if (rc == 0) {
		/* since paths are not looked up by component - the parent
		   directories are presumed to be good here */
		renew_parental_timestamps(direntry);
	} else if (rc == -ENOENT) {
		cifs_set_time(direntry, jiffies);
		newInode = NULL;
	} else {
		if (rc != -EACCES) {
			cifs_dbg(FYI, "Unexpected lookup error %d\n", rc);
			/* We special case check for Access Denied - since that
			is a common return code */
		}
		newInode = ERR_PTR(rc);
	}
	kfree(full_path);
	cifs_put_tlink(tlink);
	free_xid(xid);
	return d_splice_alias(newInode, direntry);
}