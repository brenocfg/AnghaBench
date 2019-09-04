#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct svc_cred {int /*<<< orphan*/  cr_flavor; TYPE_3__* cr_group_info; void* cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_6__ {struct kvec* head; } ;
struct TYPE_5__ {struct kvec* head; } ;
struct svc_rqst {struct svc_cred rq_cred; TYPE_2__ rq_res; TYPE_1__ rq_arg; } ;
struct kvec {int iov_len; void* iov_base; } ;
typedef  void* kgid_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {void** gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int SVC_CLOSE ; 
 int SVC_DENIED ; 
 int SVC_GARBAGE ; 
 int SVC_OK ; 
 int UNX_NGROUPS ; 
 int XDR_QUADLEN (int) ; 
 TYPE_3__* groups_alloc (int) ; 
 int /*<<< orphan*/  groups_sort (TYPE_3__*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 void* make_kgid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int /*<<< orphan*/  rpc_autherr_badverf ; 
 int svc_getnl (struct kvec*) ; 
 scalar_t__ svc_getu32 (struct kvec*) ; 
 int /*<<< orphan*/  svc_putnl (struct kvec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
svcauth_unix_accept(struct svc_rqst *rqstp, __be32 *authp)
{
	struct kvec	*argv = &rqstp->rq_arg.head[0];
	struct kvec	*resv = &rqstp->rq_res.head[0];
	struct svc_cred	*cred = &rqstp->rq_cred;
	u32		slen, i;
	int		len   = argv->iov_len;

	if ((len -= 3*4) < 0)
		return SVC_GARBAGE;

	svc_getu32(argv);			/* length */
	svc_getu32(argv);			/* time stamp */
	slen = XDR_QUADLEN(svc_getnl(argv));	/* machname length */
	if (slen > 64 || (len -= (slen + 3)*4) < 0)
		goto badcred;
	argv->iov_base = (void*)((__be32*)argv->iov_base + slen);	/* skip machname */
	argv->iov_len -= slen*4;
	/*
	 * Note: we skip uid_valid()/gid_valid() checks here for
	 * backwards compatibility with clients that use -1 id's.
	 * Instead, -1 uid or gid is later mapped to the
	 * (export-specific) anonymous id by nfsd_setuser.
	 * Supplementary gid's will be left alone.
	 */
	cred->cr_uid = make_kuid(&init_user_ns, svc_getnl(argv)); /* uid */
	cred->cr_gid = make_kgid(&init_user_ns, svc_getnl(argv)); /* gid */
	slen = svc_getnl(argv);			/* gids length */
	if (slen > UNX_NGROUPS || (len -= (slen + 2)*4) < 0)
		goto badcred;
	cred->cr_group_info = groups_alloc(slen);
	if (cred->cr_group_info == NULL)
		return SVC_CLOSE;
	for (i = 0; i < slen; i++) {
		kgid_t kgid = make_kgid(&init_user_ns, svc_getnl(argv));
		cred->cr_group_info->gid[i] = kgid;
	}
	groups_sort(cred->cr_group_info);
	if (svc_getu32(argv) != htonl(RPC_AUTH_NULL) || svc_getu32(argv) != 0) {
		*authp = rpc_autherr_badverf;
		return SVC_DENIED;
	}

	/* Put NULL verifier */
	svc_putnl(resv, RPC_AUTH_NULL);
	svc_putnl(resv, 0);

	rqstp->rq_cred.cr_flavor = RPC_AUTH_UNIX;
	return SVC_OK;

badcred:
	*authp = rpc_autherr_badcred;
	return SVC_DENIED;
}