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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ ss_family; } ;
struct svc_rqst {TYPE_1__ rq_daddr; } ;
struct super_block {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int netid_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  netid; } ;
struct pnfs_ff_device_addr {int version; int tightly_coupled; TYPE_2__ netaddr; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; scalar_t__ minor_version; } ;
struct nfsd4_getdeviceinfo {struct pnfs_ff_device_addr* gd_device; } ;
struct nfs4_client {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FF_ADDR_LEN ; 
 scalar_t__ FF_NETID_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INET6_ADDRSTRLEN ; 
 struct pnfs_ff_device_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_ntop (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  svc_max_payload (struct svc_rqst*) ; 

__attribute__((used)) static __be32
nfsd4_ff_proc_getdeviceinfo(struct super_block *sb, struct svc_rqst *rqstp,
		struct nfs4_client *clp, struct nfsd4_getdeviceinfo *gdp)
{
	struct pnfs_ff_device_addr *da;

	u16 port;
	char addr[INET6_ADDRSTRLEN];

	da = kzalloc(sizeof(struct pnfs_ff_device_addr), GFP_KERNEL);
	if (!da)
		return nfserrno(-ENOMEM);

	gdp->gd_device = da;

	da->version = 3;
	da->minor_version = 0;

	da->rsize = svc_max_payload(rqstp);
	da->wsize = da->rsize;

	rpc_ntop((struct sockaddr *)&rqstp->rq_daddr,
		 addr, INET6_ADDRSTRLEN);
	if (rqstp->rq_daddr.ss_family == AF_INET) {
		struct sockaddr_in *sin;

		sin = (struct sockaddr_in *)&rqstp->rq_daddr;
		port = ntohs(sin->sin_port);
		snprintf(da->netaddr.netid, FF_NETID_LEN + 1, "tcp");
		da->netaddr.netid_len = 3;
	} else {
		struct sockaddr_in6 *sin6;

		sin6 = (struct sockaddr_in6 *)&rqstp->rq_daddr;
		port = ntohs(sin6->sin6_port);
		snprintf(da->netaddr.netid, FF_NETID_LEN + 1, "tcp6");
		da->netaddr.netid_len = 4;
	}

	da->netaddr.addr_len =
		snprintf(da->netaddr.addr, FF_ADDR_LEN + 1,
			 "%s.%hhu.%hhu", addr, port >> 8, port & 0xff);

	da->tightly_coupled = false;

	return 0;
}