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
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr {int dummy; } ;
struct rpc_timeout {int dummy; } ;
struct nfs_server {int flags; int /*<<< orphan*/  cred; struct nfs_client* nfs_client; } ;
struct nfs_client_initdata {int addrlen; int proto; char* hostname; int nconnect; int /*<<< orphan*/  init_flags; int /*<<< orphan*/  cred; struct rpc_timeout* timeparms; int /*<<< orphan*/  net; int /*<<< orphan*/  minorversion; int /*<<< orphan*/ * nfs_mod; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  nodename; struct sockaddr const* addr; } ;
struct nfs_client {int cl_nconnect; int /*<<< orphan*/  cl_net; int /*<<< orphan*/  cl_ipaddr; TYPE_1__* cl_rpcclient; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  cl_nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nfs_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  NFS_CS_NORESVPORT ; 
 int NFS_MOUNT_NORESVPORT ; 
 int XPRT_TRANSPORT_TCP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfs_client* nfs_get_client (struct nfs_client_initdata*) ; 
 int /*<<< orphan*/  nfs_init_timeout_values (struct rpc_timeout*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_v4 ; 
 scalar_t__ rpc_ntop (struct sockaddr const*,char*,int) ; 

struct nfs_client *nfs4_set_ds_client(struct nfs_server *mds_srv,
		const struct sockaddr *ds_addr, int ds_addrlen,
		int ds_proto, unsigned int ds_timeo, unsigned int ds_retrans,
		u32 minor_version)
{
	struct rpc_timeout ds_timeout;
	struct nfs_client *mds_clp = mds_srv->nfs_client;
	struct nfs_client_initdata cl_init = {
		.addr = ds_addr,
		.addrlen = ds_addrlen,
		.nodename = mds_clp->cl_rpcclient->cl_nodename,
		.ip_addr = mds_clp->cl_ipaddr,
		.nfs_mod = &nfs_v4,
		.proto = ds_proto,
		.minorversion = minor_version,
		.net = mds_clp->cl_net,
		.timeparms = &ds_timeout,
		.cred = mds_srv->cred,
	};
	char buf[INET6_ADDRSTRLEN + 1];

	if (rpc_ntop(ds_addr, buf, sizeof(buf)) <= 0)
		return ERR_PTR(-EINVAL);
	cl_init.hostname = buf;

	if (mds_clp->cl_nconnect > 1 && ds_proto == XPRT_TRANSPORT_TCP)
		cl_init.nconnect = mds_clp->cl_nconnect;

	if (mds_srv->flags & NFS_MOUNT_NORESVPORT)
		__set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);

	/*
	 * Set an authflavor equual to the MDS value. Use the MDS nfs_client
	 * cl_ipaddr so as to use the same EXCHANGE_ID co_ownerid as the MDS
	 * (section 13.1 RFC 5661).
	 */
	nfs_init_timeout_values(&ds_timeout, ds_proto, ds_timeo, ds_retrans);
	return nfs_get_client(&cl_init);
}