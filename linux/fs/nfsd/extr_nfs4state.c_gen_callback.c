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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_daddrlen; int /*<<< orphan*/  rq_daddr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr {int dummy; } ;
struct nfsd4_setclientid {int se_callback_netid_len; int /*<<< orphan*/  se_callback_ident; int /*<<< orphan*/  se_callback_prog; int /*<<< orphan*/  se_callback_addr_len; int /*<<< orphan*/  se_callback_addr_val; int /*<<< orphan*/  se_callback_netid_val; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct TYPE_3__ {unsigned short ss_family; } ;
struct nfs4_cb_conn {scalar_t__ cb_addrlen; TYPE_1__ cb_addr; int /*<<< orphan*/  cb_saddr; int /*<<< orphan*/  cb_ident; int /*<<< orphan*/  cb_prog; } ;
struct nfs4_client {TYPE_2__ cl_clientid; int /*<<< orphan*/  net; struct nfs4_cb_conn cl_cb_conn; } ;

/* Variables and functions */
 unsigned short AF_INET ; 
 unsigned short AF_INET6 ; 
 unsigned short AF_UNSPEC ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_get_scope_id (struct sockaddr*) ; 
 scalar_t__ rpc_uaddr2sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 

__attribute__((used)) static void
gen_callback(struct nfs4_client *clp, struct nfsd4_setclientid *se, struct svc_rqst *rqstp)
{
	struct nfs4_cb_conn *conn = &clp->cl_cb_conn;
	struct sockaddr	*sa = svc_addr(rqstp);
	u32 scopeid = rpc_get_scope_id(sa);
	unsigned short expected_family;

	/* Currently, we only support tcp and tcp6 for the callback channel */
	if (se->se_callback_netid_len == 3 &&
	    !memcmp(se->se_callback_netid_val, "tcp", 3))
		expected_family = AF_INET;
	else if (se->se_callback_netid_len == 4 &&
		 !memcmp(se->se_callback_netid_val, "tcp6", 4))
		expected_family = AF_INET6;
	else
		goto out_err;

	conn->cb_addrlen = rpc_uaddr2sockaddr(clp->net, se->se_callback_addr_val,
					    se->se_callback_addr_len,
					    (struct sockaddr *)&conn->cb_addr,
					    sizeof(conn->cb_addr));

	if (!conn->cb_addrlen || conn->cb_addr.ss_family != expected_family)
		goto out_err;

	if (conn->cb_addr.ss_family == AF_INET6)
		((struct sockaddr_in6 *)&conn->cb_addr)->sin6_scope_id = scopeid;

	conn->cb_prog = se->se_callback_prog;
	conn->cb_ident = se->se_callback_ident;
	memcpy(&conn->cb_saddr, &rqstp->rq_daddr, rqstp->rq_daddrlen);
	return;
out_err:
	conn->cb_addr.ss_family = AF_UNSPEC;
	conn->cb_addrlen = 0;
	dprintk("NFSD: this client (clientid %08x/%08x) "
		"will not receive delegations\n",
		clp->cl_clientid.cl_boot, clp->cl_clientid.cl_id);

	return;
}