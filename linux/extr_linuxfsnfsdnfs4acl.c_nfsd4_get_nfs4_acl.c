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
struct svc_rqst {int dummy; } ;
struct posix_acl {int a_count; } ;
struct nfs4_acl {scalar_t__ naces; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 unsigned int NFS4_ACL_DIR ; 
 unsigned int NFS4_ACL_TYPE_DEFAULT ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _posix_to_nfsv4_one (struct posix_acl*,struct nfs4_acl*,unsigned int) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct posix_acl* get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 struct nfs4_acl* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_acl_bytes (int) ; 
 struct posix_acl* posix_acl_from_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int
nfsd4_get_nfs4_acl(struct svc_rqst *rqstp, struct dentry *dentry,
		struct nfs4_acl **acl)
{
	struct inode *inode = d_inode(dentry);
	int error = 0;
	struct posix_acl *pacl = NULL, *dpacl = NULL;
	unsigned int flags = 0;
	int size = 0;

	pacl = get_acl(inode, ACL_TYPE_ACCESS);
	if (!pacl)
		pacl = posix_acl_from_mode(inode->i_mode, GFP_KERNEL);

	if (IS_ERR(pacl))
		return PTR_ERR(pacl);

	/* allocate for worst case: one (deny, allow) pair each: */
	size += 2 * pacl->a_count;

	if (S_ISDIR(inode->i_mode)) {
		flags = NFS4_ACL_DIR;
		dpacl = get_acl(inode, ACL_TYPE_DEFAULT);
		if (IS_ERR(dpacl)) {
			error = PTR_ERR(dpacl);
			goto rel_pacl;
		}

		if (dpacl)
			size += 2 * dpacl->a_count;
	}

	*acl = kmalloc(nfs4_acl_bytes(size), GFP_KERNEL);
	if (*acl == NULL) {
		error = -ENOMEM;
		goto out;
	}
	(*acl)->naces = 0;

	_posix_to_nfsv4_one(pacl, *acl, flags & ~NFS4_ACL_TYPE_DEFAULT);

	if (dpacl)
		_posix_to_nfsv4_one(dpacl, *acl, flags | NFS4_ACL_TYPE_DEFAULT);

out:
	posix_acl_release(dpacl);
rel_pacl:
	posix_acl_release(pacl);
	return error;
}