#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {scalar_t__ client; TYPE_1__* nfs_client; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct TYPE_2__ {scalar_t__ cl_rpcclient; } ;

/* Variables and functions */
 int do_proc_get_root (scalar_t__,struct nfs_fh*,struct nfs_fsinfo*) ; 

__attribute__((used)) static int
nfs3_proc_get_root(struct nfs_server *server, struct nfs_fh *fhandle,
		   struct nfs_fsinfo *info)
{
	int	status;

	status = do_proc_get_root(server->client, fhandle, info);
	if (status && server->nfs_client->cl_rpcclient != server->client)
		status = do_proc_get_root(server->nfs_client->cl_rpcclient, fhandle, info);
	return status;
}