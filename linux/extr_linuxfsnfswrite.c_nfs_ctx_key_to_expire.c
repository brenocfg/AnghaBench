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
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct rpc_auth* cl_auth; } ;

/* Variables and functions */
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int rpcauth_cred_key_to_expire (struct rpc_auth*,int /*<<< orphan*/ ) ; 

bool nfs_ctx_key_to_expire(struct nfs_open_context *ctx, struct inode *inode)
{
	struct rpc_auth *auth = NFS_SERVER(inode)->client->cl_auth;

	return rpcauth_cred_key_to_expire(auth, ctx->cred);
}