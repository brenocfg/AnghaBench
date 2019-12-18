#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct user_namespace {int dummy; } ;
struct rpc_task {TYPE_1__* tk_rqstp; struct rpc_clnt* tk_client; } ;
struct rpc_cred {TYPE_3__* cr_cred; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_nodelen; int /*<<< orphan*/  cl_nodename; TYPE_2__* cl_cred; } ;
struct group_info {int ngroups; int /*<<< orphan*/ * gid; } ;
typedef  void* __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; struct group_info* group_info; } ;
struct TYPE_5__ {struct user_namespace* user_ns; } ;
struct TYPE_4__ {struct rpc_cred* rq_cred; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int UNX_NGROUPS ; 
 void* cpu_to_be32 (int) ; 
 int from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct user_namespace init_user_ns ; 
 int /*<<< orphan*/  rpc_auth_null ; 
 int /*<<< orphan*/  rpc_auth_unix ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 
 scalar_t__ xdr_stream_encode_opaque (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xdr_zero ; 

__attribute__((used)) static int
unx_marshal(struct rpc_task *task, struct xdr_stream *xdr)
{
	struct rpc_clnt	*clnt = task->tk_client;
	struct rpc_cred	*cred = task->tk_rqstp->rq_cred;
	__be32		*p, *cred_len, *gidarr_len;
	int		i;
	struct group_info *gi = cred->cr_cred->group_info;
	struct user_namespace *userns = clnt->cl_cred ?
		clnt->cl_cred->user_ns : &init_user_ns;

	/* Credential */

	p = xdr_reserve_space(xdr, 3 * sizeof(*p));
	if (!p)
		goto marshal_failed;
	*p++ = rpc_auth_unix;
	cred_len = p++;
	*p++ = xdr_zero;	/* stamp */
	if (xdr_stream_encode_opaque(xdr, clnt->cl_nodename,
				     clnt->cl_nodelen) < 0)
		goto marshal_failed;
	p = xdr_reserve_space(xdr, 3 * sizeof(*p));
	if (!p)
		goto marshal_failed;
	*p++ = cpu_to_be32(from_kuid_munged(userns, cred->cr_cred->fsuid));
	*p++ = cpu_to_be32(from_kgid_munged(userns, cred->cr_cred->fsgid));

	gidarr_len = p++;
	if (gi)
		for (i = 0; i < UNX_NGROUPS && i < gi->ngroups; i++)
			*p++ = cpu_to_be32(from_kgid_munged(userns, gi->gid[i]));
	*gidarr_len = cpu_to_be32(p - gidarr_len - 1);
	*cred_len = cpu_to_be32((p - cred_len - 1) << 2);
	p = xdr_reserve_space(xdr, (p - gidarr_len - 1) << 2);
	if (!p)
		goto marshal_failed;

	/* Verifier */

	p = xdr_reserve_space(xdr, 2 * sizeof(*p));
	if (!p)
		goto marshal_failed;
	*p++ = rpc_auth_null;
	*p   = xdr_zero;

	return 0;

marshal_failed:
	return -EMSGSIZE;
}