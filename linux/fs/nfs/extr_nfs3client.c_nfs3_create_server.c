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
struct nfs_subversion {int dummy; } ;
struct nfs_server {int dummy; } ;
struct nfs_mount_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct nfs_server*) ; 
 struct nfs_server* nfs_create_server (struct nfs_mount_info*,struct nfs_subversion*) ; 
 int /*<<< orphan*/  nfs_init_server_aclclient (struct nfs_server*) ; 

struct nfs_server *nfs3_create_server(struct nfs_mount_info *mount_info,
				      struct nfs_subversion *nfs_mod)
{
	struct nfs_server *server = nfs_create_server(mount_info, nfs_mod);
	/* Create a client RPC handle for the NFS v3 ACL management interface */
	if (!IS_ERR(server))
		nfs_init_server_aclclient(server);
	return server;
}