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
struct rpc_message {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_server {int dummy; } ;
struct nfs4_sequence_res {int dummy; } ;
struct nfs4_sequence_args {int dummy; } ;

/* Variables and functions */
 int nfs4_call_sync_sequence (struct rpc_clnt*,struct nfs_server*,struct rpc_message*,struct nfs4_sequence_args*,struct nfs4_sequence_res*) ; 
 int /*<<< orphan*/  nfs4_init_sequence (struct nfs4_sequence_args*,struct nfs4_sequence_res*,int,int /*<<< orphan*/ ) ; 

int nfs4_call_sync(struct rpc_clnt *clnt,
		   struct nfs_server *server,
		   struct rpc_message *msg,
		   struct nfs4_sequence_args *args,
		   struct nfs4_sequence_res *res,
		   int cache_reply)
{
	nfs4_init_sequence(args, res, cache_reply, 0);
	return nfs4_call_sync_sequence(clnt, server, msg, args, res);
}