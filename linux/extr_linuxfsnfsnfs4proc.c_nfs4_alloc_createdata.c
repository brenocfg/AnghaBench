#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qstr {int dummy; } ;
struct nfs_server {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fattr; int /*<<< orphan*/  label; int /*<<< orphan*/ * fh; struct nfs_server* server; } ;
struct TYPE_5__ {int /*<<< orphan*/  umask; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  ftype; struct iattr* attrs; struct qstr const* name; struct nfs_server* server; int /*<<< orphan*/  dir_fh; } ;
struct TYPE_4__ {TYPE_3__* rpc_resp; TYPE_2__* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs4_createdata {TYPE_3__ res; int /*<<< orphan*/  label; int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; TYPE_2__ arg; TYPE_1__ msg; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 size_t NFSPROC4_CLNT_CREATE ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  current_umask () ; 
 int /*<<< orphan*/  kfree (struct nfs4_createdata*) ; 
 struct nfs4_createdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_bitmask (struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_alloc (struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_createdata *nfs4_alloc_createdata(struct inode *dir,
		const struct qstr *name, struct iattr *sattr, u32 ftype)
{
	struct nfs4_createdata *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data != NULL) {
		struct nfs_server *server = NFS_SERVER(dir);

		data->label = nfs4_label_alloc(server, GFP_KERNEL);
		if (IS_ERR(data->label))
			goto out_free;

		data->msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CREATE];
		data->msg.rpc_argp = &data->arg;
		data->msg.rpc_resp = &data->res;
		data->arg.dir_fh = NFS_FH(dir);
		data->arg.server = server;
		data->arg.name = name;
		data->arg.attrs = sattr;
		data->arg.ftype = ftype;
		data->arg.bitmask = nfs4_bitmask(server, data->label);
		data->arg.umask = current_umask();
		data->res.server = server;
		data->res.fh = &data->fh;
		data->res.fattr = &data->fattr;
		data->res.label = data->label;
		nfs_fattr_init(data->res.fattr);
	}
	return data;
out_free:
	kfree(data);
	return NULL;
}