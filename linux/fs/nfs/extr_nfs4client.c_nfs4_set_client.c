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
typedef  scalar_t__ u32 ;
struct sockaddr {int dummy; } ;
struct rpc_timeout {int dummy; } ;
struct nfs_server {int flags; int options; struct nfs_client* nfs_client; int /*<<< orphan*/  port; int /*<<< orphan*/  mig_status; int /*<<< orphan*/  cred; } ;
struct nfs_client_initdata {char const* hostname; size_t const addrlen; char const* ip_addr; int proto; scalar_t__ minorversion; unsigned int nconnect; int /*<<< orphan*/  init_flags; int /*<<< orphan*/  cred; struct rpc_timeout const* timeparms; struct net* net; int /*<<< orphan*/ * nfs_mod; struct sockaddr const* addr; } ;
struct nfs_client {int /*<<< orphan*/  cl_res_state; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ELOOP ; 
 scalar_t__ IS_ERR (struct nfs_client*) ; 
 int /*<<< orphan*/  NFS_CS_CHECK_LEASE_TIME ; 
 int /*<<< orphan*/  NFS_CS_MIGRATION ; 
 int /*<<< orphan*/  NFS_CS_NORESVPORT ; 
 int /*<<< orphan*/  NFS_CS_TSM_POSSIBLE ; 
 int /*<<< orphan*/  NFS_MIG_TSM_POSSIBLE ; 
 int NFS_MOUNT_NORESVPORT ; 
 int NFS_OPTION_MIGRATION ; 
 int PTR_ERR (struct nfs_client*) ; 
 int XPRT_TRANSPORT_TCP ; 
 struct nfs_client* nfs_get_client (struct nfs_client_initdata*) ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_v4 ; 
 int /*<<< orphan*/  rpc_get_port (struct sockaddr const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_set_client(struct nfs_server *server,
		const char *hostname,
		const struct sockaddr *addr,
		const size_t addrlen,
		const char *ip_addr,
		int proto, const struct rpc_timeout *timeparms,
		u32 minorversion, unsigned int nconnect,
		struct net *net)
{
	struct nfs_client_initdata cl_init = {
		.hostname = hostname,
		.addr = addr,
		.addrlen = addrlen,
		.ip_addr = ip_addr,
		.nfs_mod = &nfs_v4,
		.proto = proto,
		.minorversion = minorversion,
		.net = net,
		.timeparms = timeparms,
		.cred = server->cred,
	};
	struct nfs_client *clp;

	if (minorversion > 0 && proto == XPRT_TRANSPORT_TCP)
		cl_init.nconnect = nconnect;
	if (server->flags & NFS_MOUNT_NORESVPORT)
		set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);
	if (server->options & NFS_OPTION_MIGRATION)
		set_bit(NFS_CS_MIGRATION, &cl_init.init_flags);
	if (test_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status))
		set_bit(NFS_CS_TSM_POSSIBLE, &cl_init.init_flags);
	server->port = rpc_get_port(addr);

	/* Allocate or find a client reference we can use */
	clp = nfs_get_client(&cl_init);
	if (IS_ERR(clp))
		return PTR_ERR(clp);

	if (server->nfs_client == clp) {
		nfs_put_client(clp);
		return -ELOOP;
	}

	/*
	 * Query for the lease time on clientid setup or renewal
	 *
	 * Note that this will be set on nfs_clients that were created
	 * only for the DS role and did not set this bit, but now will
	 * serve a dual role.
	 */
	set_bit(NFS_CS_CHECK_LEASE_TIME, &clp->cl_res_state);

	server->nfs_client = clp;
	return 0;
}