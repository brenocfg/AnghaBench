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
struct rpc_cred {unsigned long cr_flags; } ;
struct unx_cred {struct rpc_cred uc_base; int /*<<< orphan*/ * uc_gids; int /*<<< orphan*/  uc_gid; } ;
struct rpc_auth {int dummy; } ;
struct auth_cred {TYPE_1__* group_info; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {unsigned int ngroups; int /*<<< orphan*/ * gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rpc_cred* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_GID ; 
 unsigned long RPCAUTH_CRED_UPTODATE ; 
 unsigned int UNX_NGROUPS ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct unx_cred* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcauth_init_cred (struct rpc_cred*,struct auth_cred*,struct rpc_auth*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_credops ; 

__attribute__((used)) static struct rpc_cred *
unx_create_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags, gfp_t gfp)
{
	struct unx_cred	*cred;
	unsigned int groups = 0;
	unsigned int i;

	dprintk("RPC:       allocating UNIX cred for uid %d gid %d\n",
			from_kuid(&init_user_ns, acred->uid),
			from_kgid(&init_user_ns, acred->gid));

	if (!(cred = kmalloc(sizeof(*cred), gfp)))
		return ERR_PTR(-ENOMEM);

	rpcauth_init_cred(&cred->uc_base, acred, auth, &unix_credops);
	cred->uc_base.cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;

	if (acred->group_info != NULL)
		groups = acred->group_info->ngroups;
	if (groups > UNX_NGROUPS)
		groups = UNX_NGROUPS;

	cred->uc_gid = acred->gid;
	for (i = 0; i < groups; i++)
		cred->uc_gids[i] = acred->group_info->gid[i];
	if (i < UNX_NGROUPS)
		cred->uc_gids[i] = INVALID_GID;

	return &cred->uc_base;
}