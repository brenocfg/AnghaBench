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
struct inode {int i_mode; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_valid; int ia_mode; scalar_t__ ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int mnt_dir_mode; int mnt_file_mode; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_FORCE ; 
 int ATTR_GID ; 
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_NORMAL ; 
 int ATTR_READONLY ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_DYNPERM ; 
 int CIFS_MOUNT_NO_PERM ; 
 int CIFS_MOUNT_SET_UID ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int NO_CHANGE_64 ; 
 int S_IALLUGO ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWUGO ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct dentry*,int) ; 
 int cifs_set_file_info (struct inode*,struct iattr*,unsigned int,char*,int) ; 
 int cifs_set_file_size (struct inode*,struct iattr*,unsigned int,char*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

__attribute__((used)) static int
cifs_setattr_nounix(struct dentry *direntry, struct iattr *attrs)
{
	unsigned int xid;
	kuid_t uid = INVALID_UID;
	kgid_t gid = INVALID_GID;
	struct inode *inode = d_inode(direntry);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct cifsInodeInfo *cifsInode = CIFS_I(inode);
	char *full_path = NULL;
	int rc = -EACCES;
	__u32 dosattr = 0;
	__u64 mode = NO_CHANGE_64;

	xid = get_xid();

	cifs_dbg(FYI, "setattr on file %pd attrs->iavalid 0x%x\n",
		 direntry, attrs->ia_valid);

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_PERM)
		attrs->ia_valid |= ATTR_FORCE;

	rc = setattr_prepare(direntry, attrs);
	if (rc < 0) {
		free_xid(xid);
		return rc;
	}

	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		free_xid(xid);
		return rc;
	}

	/*
	 * Attempt to flush data before changing attributes. We need to do
	 * this for ATTR_SIZE and ATTR_MTIME for sure, and if we change the
	 * ownership or mode then we may also need to do this. Here, we take
	 * the safe way out and just do the flush on all setattr requests. If
	 * the flush returns error, store it to report later and continue.
	 *
	 * BB: This should be smarter. Why bother flushing pages that
	 * will be truncated anyway? Also, should we error out here if
	 * the flush returns error?
	 */
	rc = filemap_write_and_wait(inode->i_mapping);
	mapping_set_error(inode->i_mapping, rc);
	rc = 0;

	if (attrs->ia_valid & ATTR_SIZE) {
		rc = cifs_set_file_size(inode, attrs, xid, full_path);
		if (rc != 0)
			goto cifs_setattr_exit;
	}

	if (attrs->ia_valid & ATTR_UID)
		uid = attrs->ia_uid;

	if (attrs->ia_valid & ATTR_GID)
		gid = attrs->ia_gid;

#ifdef CONFIG_CIFS_ACL
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) {
		if (uid_valid(uid) || gid_valid(gid)) {
			rc = id_mode_to_cifs_acl(inode, full_path, NO_CHANGE_64,
							uid, gid);
			if (rc) {
				cifs_dbg(FYI, "%s: Setting id failed with error: %d\n",
					 __func__, rc);
				goto cifs_setattr_exit;
			}
		}
	} else
#endif /* CONFIG_CIFS_ACL */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SET_UID))
		attrs->ia_valid &= ~(ATTR_UID | ATTR_GID);

	/* skip mode change if it's just for clearing setuid/setgid */
	if (attrs->ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID))
		attrs->ia_valid &= ~ATTR_MODE;

	if (attrs->ia_valid & ATTR_MODE) {
		mode = attrs->ia_mode;
		rc = 0;
#ifdef CONFIG_CIFS_ACL
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) {
			rc = id_mode_to_cifs_acl(inode, full_path, mode,
						INVALID_UID, INVALID_GID);
			if (rc) {
				cifs_dbg(FYI, "%s: Setting ACL failed with error: %d\n",
					 __func__, rc);
				goto cifs_setattr_exit;
			}
		} else
#endif /* CONFIG_CIFS_ACL */
		if (((mode & S_IWUGO) == 0) &&
		    (cifsInode->cifsAttrs & ATTR_READONLY) == 0) {

			dosattr = cifsInode->cifsAttrs | ATTR_READONLY;

			/* fix up mode if we're not using dynperm */
			if ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM) == 0)
				attrs->ia_mode = inode->i_mode & ~S_IWUGO;
		} else if ((mode & S_IWUGO) &&
			   (cifsInode->cifsAttrs & ATTR_READONLY)) {

			dosattr = cifsInode->cifsAttrs & ~ATTR_READONLY;
			/* Attributes of 0 are ignored */
			if (dosattr == 0)
				dosattr |= ATTR_NORMAL;

			/* reset local inode permissions to normal */
			if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM)) {
				attrs->ia_mode &= ~(S_IALLUGO);
				if (S_ISDIR(inode->i_mode))
					attrs->ia_mode |=
						cifs_sb->mnt_dir_mode;
				else
					attrs->ia_mode |=
						cifs_sb->mnt_file_mode;
			}
		} else if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM)) {
			/* ignore mode change - ATTR_READONLY hasn't changed */
			attrs->ia_valid &= ~ATTR_MODE;
		}
	}

	if (attrs->ia_valid & (ATTR_MTIME|ATTR_ATIME|ATTR_CTIME) ||
	    ((attrs->ia_valid & ATTR_MODE) && dosattr)) {
		rc = cifs_set_file_info(inode, attrs, xid, full_path, dosattr);
		/* BB: check for rc = -EOPNOTSUPP and switch to legacy mode */

		/* Even if error on time set, no sense failing the call if
		the server would set the time to a reasonable value anyway,
		and this check ensures that we are not being called from
		sys_utimes in which case we ought to fail the call back to
		the user when the server rejects the call */
		if ((rc) && (attrs->ia_valid &
				(ATTR_MODE | ATTR_GID | ATTR_UID | ATTR_SIZE)))
			rc = 0;
	}

	/* do not need local check to inode_check_ok since the server does
	   that */
	if (rc)
		goto cifs_setattr_exit;

	if ((attrs->ia_valid & ATTR_SIZE) &&
	    attrs->ia_size != i_size_read(inode))
		truncate_setsize(inode, attrs->ia_size);

	setattr_copy(inode, attrs);
	mark_inode_dirty(inode);

cifs_setattr_exit:
	kfree(full_path);
	free_xid(xid);
	return rc;
}