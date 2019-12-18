#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xattr_handler {int flags; } ;
struct tcon_link {int dummy; } ;
struct super_block {int s_flags; } ;
struct inode {int dummy; } ;
struct dentry {struct super_block* d_sb; } ;
struct cifs_tcon {TYPE_3__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  char cifs_ntsd ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {int /*<<< orphan*/  time; } ;
struct TYPE_7__ {TYPE_2__* server; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* set_EA ) (unsigned int,struct cifs_tcon*,char*,char const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_sb_info*) ;int (* set_acl ) (char*,size_t,struct inode*,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int CIFSSMBSetPosixACL (unsigned int,struct cifs_tcon*,char*,void const*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_ACL_DACL ; 
 TYPE_4__* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_NO_XATTR ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 size_t MAX_EA_VALUE_SIZE ; 
 int PTR_ERR (struct tcon_link*) ; 
 int SB_POSIXACL ; 
#define  XATTR_ACL_ACCESS 131 
#define  XATTR_ACL_DEFAULT 130 
#define  XATTR_CIFS_ACL 129 
#define  XATTR_USER 128 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_remap (struct cifs_sb_info*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int stub1 (unsigned int,struct cifs_tcon*,char*,char const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_sb_info*) ; 
 int stub2 (char*,size_t,struct inode*,char*,int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int cifs_xattr_set(const struct xattr_handler *handler,
			  struct dentry *dentry, struct inode *inode,
			  const char *name, const void *value,
			  size_t size, int flags)
{
	int rc = -EOPNOTSUPP;
	unsigned int xid;
	struct super_block *sb = dentry->d_sb;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	char *full_path;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = get_xid();

	full_path = build_path_from_dentry(dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto out;
	}
	/* return dos attributes as pseudo xattr */
	/* return alt name if available as pseudo attr */

	/* if proc/fs/cifs/streamstoxattr is set then
		search server for EAs or streams to
		returns as xattrs */
	if (size > MAX_EA_VALUE_SIZE) {
		cifs_dbg(FYI, "size of EA value too large\n");
		rc = -EOPNOTSUPP;
		goto out;
	}

	switch (handler->flags) {
	case XATTR_USER:
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_XATTR)
			goto out;

		if (pTcon->ses->server->ops->set_EA)
			rc = pTcon->ses->server->ops->set_EA(xid, pTcon,
				full_path, name, value, (__u16)size,
				cifs_sb->local_nls, cifs_sb);
		break;

	case XATTR_CIFS_ACL: {
		struct cifs_ntsd *pacl;

		if (!value)
			goto out;
		pacl = kmalloc(size, GFP_KERNEL);
		if (!pacl) {
			rc = -ENOMEM;
		} else {
			memcpy(pacl, value, size);
			if (value &&
			    pTcon->ses->server->ops->set_acl)
				rc = pTcon->ses->server->ops->set_acl(pacl,
						size, inode,
						full_path, CIFS_ACL_DACL);
			else
				rc = -EOPNOTSUPP;
			if (rc == 0) /* force revalidate of the inode */
				CIFS_I(inode)->time = 0;
			kfree(pacl);
		}
		break;
	}

	case XATTR_ACL_ACCESS:
#ifdef CONFIG_CIFS_POSIX
		if (!value)
			goto out;
		if (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBSetPosixACL(xid, pTcon, full_path,
				value, (const int)size,
				ACL_TYPE_ACCESS, cifs_sb->local_nls,
				cifs_remap(cifs_sb));
#endif  /* CONFIG_CIFS_POSIX */
		break;

	case XATTR_ACL_DEFAULT:
#ifdef CONFIG_CIFS_POSIX
		if (!value)
			goto out;
		if (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBSetPosixACL(xid, pTcon, full_path,
				value, (const int)size,
				ACL_TYPE_DEFAULT, cifs_sb->local_nls,
				cifs_remap(cifs_sb));
#endif  /* CONFIG_CIFS_POSIX */
		break;
	}

out:
	kfree(full_path);
	free_xid(xid);
	cifs_put_tlink(tlink);
	return rc;
}