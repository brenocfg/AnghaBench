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
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cl_mvops; } ;
struct TYPE_3__ {int (* find_root_sec ) (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ;} ;

/* Variables and functions */
 int NFS4ERR_WRONGSEC ; 
 int nfs4_do_fsinfo (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 int nfs4_lookup_root (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 int nfs4_map_errors (int) ; 
 int nfs4_server_capabilities (struct nfs_server*,struct nfs_fh*) ; 
 int stub1 (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 

int nfs4_proc_get_rootfh(struct nfs_server *server, struct nfs_fh *fhandle,
			 struct nfs_fsinfo *info,
			 bool auth_probe)
{
	int status = 0;

	if (!auth_probe)
		status = nfs4_lookup_root(server, fhandle, info);

	if (auth_probe || status == NFS4ERR_WRONGSEC)
		status = server->nfs_client->cl_mvops->find_root_sec(server,
				fhandle, info);

	if (status == 0)
		status = nfs4_server_capabilities(server, fhandle);
	if (status == 0)
		status = nfs4_do_fsinfo(server, fhandle, info);

	return nfs4_map_errors(status);
}