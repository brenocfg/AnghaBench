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
struct svc_cred {int /*<<< orphan*/  cr_flavor; int /*<<< orphan*/ * cr_group_info; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_4__ {struct kvec* head; } ;
struct TYPE_3__ {struct kvec* head; } ;
struct svc_rqst {struct svc_cred rq_cred; TYPE_2__ rq_res; TYPE_1__ rq_arg; } ;
struct kvec {int iov_len; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int SVC_CLOSE ; 
 int SVC_DENIED ; 
 int SVC_GARBAGE ; 
 int SVC_OK ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/ * groups_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int /*<<< orphan*/  rpc_autherr_badverf ; 
 scalar_t__ svc_getu32 (struct kvec*) ; 
 int /*<<< orphan*/  svc_putnl (struct kvec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
svcauth_null_accept(struct svc_rqst *rqstp, __be32 *authp)
{
	struct kvec	*argv = &rqstp->rq_arg.head[0];
	struct kvec	*resv = &rqstp->rq_res.head[0];
	struct svc_cred	*cred = &rqstp->rq_cred;

	if (argv->iov_len < 3*4)
		return SVC_GARBAGE;

	if (svc_getu32(argv) != 0) {
		dprintk("svc: bad null cred\n");
		*authp = rpc_autherr_badcred;
		return SVC_DENIED;
	}
	if (svc_getu32(argv) != htonl(RPC_AUTH_NULL) || svc_getu32(argv) != 0) {
		dprintk("svc: bad null verf\n");
		*authp = rpc_autherr_badverf;
		return SVC_DENIED;
	}

	/* Signal that mapping to nobody uid/gid is required */
	cred->cr_uid = INVALID_UID;
	cred->cr_gid = INVALID_GID;
	cred->cr_group_info = groups_alloc(0);
	if (cred->cr_group_info == NULL)
		return SVC_CLOSE; /* kmalloc failure - client must retry */

	/* Put NULL verifier */
	svc_putnl(resv, RPC_AUTH_NULL);
	svc_putnl(resv, 0);

	rqstp->rq_cred.cr_flavor = RPC_AUTH_NULL;
	return SVC_OK;
}