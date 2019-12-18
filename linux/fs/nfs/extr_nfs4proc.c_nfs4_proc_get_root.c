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
struct nfs_server {int /*<<< orphan*/  fsid; } ;
struct nfs_fsinfo {struct nfs_fattr* fattr; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/  fsid; } ;
struct nfs4_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nfs4_label*) ; 
 int NFS_ATTR_FATTR_FSID ; 
 int PTR_ERR (struct nfs4_label*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nfs4_label* nfs4_label_alloc (struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_free (struct nfs4_label*) ; 
 int nfs4_proc_getattr (struct nfs_server*,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*,int /*<<< orphan*/ *) ; 
 int nfs4_server_capabilities (struct nfs_server*,struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_fsid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_proc_get_root(struct nfs_server *server, struct nfs_fh *mntfh,
			      struct nfs_fsinfo *info)
{
	int error;
	struct nfs_fattr *fattr = info->fattr;
	struct nfs4_label *label = NULL;

	error = nfs4_server_capabilities(server, mntfh);
	if (error < 0) {
		dprintk("nfs4_get_root: getcaps error = %d\n", -error);
		return error;
	}

	label = nfs4_label_alloc(server, GFP_KERNEL);
	if (IS_ERR(label))
		return PTR_ERR(label);

	error = nfs4_proc_getattr(server, mntfh, fattr, label, NULL);
	if (error < 0) {
		dprintk("nfs4_get_root: getattr error = %d\n", -error);
		goto err_free_label;
	}

	if (fattr->valid & NFS_ATTR_FATTR_FSID &&
	    !nfs_fsid_equal(&server->fsid, &fattr->fsid))
		memcpy(&server->fsid, &fattr->fsid, sizeof(server->fsid));

err_free_label:
	nfs4_label_free(label);

	return error;
}