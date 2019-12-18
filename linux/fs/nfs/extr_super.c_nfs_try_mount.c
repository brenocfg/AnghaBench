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
struct nfs_subversion {TYPE_2__* rpc_ops; } ;
struct nfs_server {int dummy; } ;
struct nfs_mount_info {TYPE_1__* parsed; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct nfs_server* (* create_server ) (struct nfs_mount_info*,struct nfs_subversion*) ;} ;
struct TYPE_3__ {scalar_t__ need_mount; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct nfs_server*) ; 
 scalar_t__ IS_ERR (struct nfs_server*) ; 
 struct dentry* nfs_fs_mount_common (struct nfs_server*,int,char const*,struct nfs_mount_info*,struct nfs_subversion*) ; 
 struct nfs_server* nfs_try_mount_request (struct nfs_mount_info*,struct nfs_subversion*) ; 
 struct nfs_server* stub1 (struct nfs_mount_info*,struct nfs_subversion*) ; 

struct dentry *nfs_try_mount(int flags, const char *dev_name,
			     struct nfs_mount_info *mount_info,
			     struct nfs_subversion *nfs_mod)
{
	struct nfs_server *server;

	if (mount_info->parsed->need_mount)
		server = nfs_try_mount_request(mount_info, nfs_mod);
	else
		server = nfs_mod->rpc_ops->create_server(mount_info, nfs_mod);

	if (IS_ERR(server))
		return ERR_CAST(server);

	return nfs_fs_mount_common(server, flags, dev_name, mount_info, nfs_mod);
}