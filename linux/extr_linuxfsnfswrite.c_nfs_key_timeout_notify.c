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
struct rpc_auth {int dummy; } ;
struct nfs_open_context {int /*<<< orphan*/  cred; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct rpc_auth* cl_auth; } ;

/* Variables and functions */
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int rpcauth_key_timeout_notify (struct rpc_auth*,int /*<<< orphan*/ ) ; 

int
nfs_key_timeout_notify(struct file *filp, struct inode *inode)
{
	struct nfs_open_context *ctx = nfs_file_open_context(filp);
	struct rpc_auth *auth = NFS_SERVER(inode)->client->cl_auth;

	return rpcauth_key_timeout_notify(auth, ctx->cred);
}