#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct posix_acl {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  fattr; int /*<<< orphan*/  dir_attr; } ;
struct TYPE_9__ {int createmode; void** verifier; struct iattr* sattr; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
struct TYPE_10__ {TYPE_3__ create; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rpc_proc; } ;
struct nfs3_createdata {TYPE_5__ res; TYPE_4__ arg; TYPE_1__ msg; } ;
struct inode {int dummy; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 size_t NFS3PROC_CREATE ; 
#define  NFS3_CREATE_EXCLUSIVE 130 
#define  NFS3_CREATE_GUARDED 129 
#define  NFS3_CREATE_UNCHECKED 128 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int O_EXCL ; 
 int PTR_ERR_OR_ZERO (struct dentry*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct nfs3_createdata* nfs3_alloc_createdata () ; 
 struct dentry* nfs3_do_create (struct inode*,struct dentry*,struct nfs3_createdata*) ; 
 int /*<<< orphan*/  nfs3_free_createdata (struct nfs3_createdata*) ; 
 int nfs3_proc_setacls (int /*<<< orphan*/ ,struct posix_acl*,struct posix_acl*) ; 
 int nfs3_proc_setattr (struct dentry*,int /*<<< orphan*/ ,struct iattr*) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int posix_acl_create (struct inode*,int /*<<< orphan*/ *,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

__attribute__((used)) static int
nfs3_proc_create(struct inode *dir, struct dentry *dentry, struct iattr *sattr,
		 int flags)
{
	struct posix_acl *default_acl, *acl;
	struct nfs3_createdata *data;
	struct dentry *d_alias;
	int status = -ENOMEM;

	dprintk("NFS call  create %pd\n", dentry);

	data = nfs3_alloc_createdata();
	if (data == NULL)
		goto out;

	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_CREATE];
	data->arg.create.fh = NFS_FH(dir);
	data->arg.create.name = dentry->d_name.name;
	data->arg.create.len = dentry->d_name.len;
	data->arg.create.sattr = sattr;

	data->arg.create.createmode = NFS3_CREATE_UNCHECKED;
	if (flags & O_EXCL) {
		data->arg.create.createmode  = NFS3_CREATE_EXCLUSIVE;
		data->arg.create.verifier[0] = cpu_to_be32(jiffies);
		data->arg.create.verifier[1] = cpu_to_be32(current->pid);
	}

	status = posix_acl_create(dir, &sattr->ia_mode, &default_acl, &acl);
	if (status)
		goto out;

	for (;;) {
		d_alias = nfs3_do_create(dir, dentry, data);
		status = PTR_ERR_OR_ZERO(d_alias);

		if (status != -ENOTSUPP)
			break;
		/* If the server doesn't support the exclusive creation
		 * semantics, try again with simple 'guarded' mode. */
		switch (data->arg.create.createmode) {
			case NFS3_CREATE_EXCLUSIVE:
				data->arg.create.createmode = NFS3_CREATE_GUARDED;
				break;

			case NFS3_CREATE_GUARDED:
				data->arg.create.createmode = NFS3_CREATE_UNCHECKED;
				break;

			case NFS3_CREATE_UNCHECKED:
				goto out;
		}
		nfs_fattr_init(data->res.dir_attr);
		nfs_fattr_init(data->res.fattr);
	}

	if (status != 0)
		goto out_release_acls;

	if (d_alias)
		dentry = d_alias;

	/* When we created the file with exclusive semantics, make
	 * sure we set the attributes afterwards. */
	if (data->arg.create.createmode == NFS3_CREATE_EXCLUSIVE) {
		dprintk("NFS call  setattr (post-create)\n");

		if (!(sattr->ia_valid & ATTR_ATIME_SET))
			sattr->ia_valid |= ATTR_ATIME;
		if (!(sattr->ia_valid & ATTR_MTIME_SET))
			sattr->ia_valid |= ATTR_MTIME;

		/* Note: we could use a guarded setattr here, but I'm
		 * not sure this buys us anything (and I'd have
		 * to revamp the NFSv3 XDR code) */
		status = nfs3_proc_setattr(dentry, data->res.fattr, sattr);
		nfs_post_op_update_inode(d_inode(dentry), data->res.fattr);
		dprintk("NFS reply setattr (post-create): %d\n", status);
		if (status != 0)
			goto out_dput;
	}

	status = nfs3_proc_setacls(d_inode(dentry), acl, default_acl);

out_dput:
	dput(d_alias);
out_release_acls:
	posix_acl_release(acl);
	posix_acl_release(default_acl);
out:
	nfs3_free_createdata(data);
	dprintk("NFS reply create: %d\n", status);
	return status;
}