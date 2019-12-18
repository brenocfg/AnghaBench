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
struct xprt_create {size_t addrlen; char const* servername; struct sockaddr* dstaddr; struct net* net; int /*<<< orphan*/  ident; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_timeout; } ;
struct nfs_server {struct nfs_client* nfs_client; int /*<<< orphan*/  mig_status; struct rpc_clnt* client; } ;
struct nfs_client {int /*<<< orphan*/ * cl_hostname; int /*<<< orphan*/  cl_nconnect; int /*<<< orphan*/  cl_minorversion; int /*<<< orphan*/  cl_proto; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  NFS_MIG_TSM_POSSIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int nfs4_set_client (struct nfs_server*,char const*,struct sockaddr*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*) ; 
 int nfs_probe_destination (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_server_insert_lists (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_server_remove_lists (struct nfs_server*) ; 
 int rpc_localaddr (struct rpc_clnt*,struct sockaddr*,int) ; 
 scalar_t__ rpc_ntop (struct sockaddr*,char*,int) ; 
 int rpc_switch_client_transport (struct rpc_clnt*,struct xprt_create*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfs4_update_server(struct nfs_server *server, const char *hostname,
		       struct sockaddr *sap, size_t salen, struct net *net)
{
	struct nfs_client *clp = server->nfs_client;
	struct rpc_clnt *clnt = server->client;
	struct xprt_create xargs = {
		.ident		= clp->cl_proto,
		.net		= net,
		.dstaddr	= sap,
		.addrlen	= salen,
		.servername	= hostname,
	};
	char buf[INET6_ADDRSTRLEN + 1];
	struct sockaddr_storage address;
	struct sockaddr *localaddr = (struct sockaddr *)&address;
	int error;

	error = rpc_switch_client_transport(clnt, &xargs, clnt->cl_timeout);
	if (error != 0)
		return error;

	error = rpc_localaddr(clnt, localaddr, sizeof(address));
	if (error != 0)
		return error;

	if (rpc_ntop(localaddr, buf, sizeof(buf)) == 0)
		return -EAFNOSUPPORT;

	nfs_server_remove_lists(server);
	set_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status);
	error = nfs4_set_client(server, hostname, sap, salen, buf,
				clp->cl_proto, clnt->cl_timeout,
				clp->cl_minorversion,
				clp->cl_nconnect, net);
	clear_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status);
	if (error != 0) {
		nfs_server_insert_lists(server);
		return error;
	}
	nfs_put_client(clp);

	if (server->nfs_client->cl_hostname == NULL)
		server->nfs_client->cl_hostname = kstrdup(hostname, GFP_KERNEL);
	nfs_server_insert_lists(server);

	return nfs_probe_destination(server);
}