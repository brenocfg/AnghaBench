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
struct rpc_cred {TYPE_2__* cr_cred; } ;
struct auth_cred {TYPE_2__* cred; } ;
struct TYPE_4__ {TYPE_1__* group_info; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct TYPE_3__ {unsigned int ngroups; int /*<<< orphan*/ * gid; } ;

/* Variables and functions */
 unsigned int UNX_NGROUPS ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unx_match(struct auth_cred *acred, struct rpc_cred *cred, int flags)
{
	unsigned int groups = 0;
	unsigned int i;

	if (cred->cr_cred == acred->cred)
		return 1;

	if (!uid_eq(cred->cr_cred->fsuid, acred->cred->fsuid) || !gid_eq(cred->cr_cred->fsgid, acred->cred->fsgid))
		return 0;

	if (acred->cred->group_info != NULL)
		groups = acred->cred->group_info->ngroups;
	if (groups > UNX_NGROUPS)
		groups = UNX_NGROUPS;
	if (cred->cr_cred->group_info == NULL)
		return groups == 0;
	if (groups != cred->cr_cred->group_info->ngroups)
		return 0;

	for (i = 0; i < groups ; i++)
		if (!gid_eq(cred->cr_cred->group_info->gid[i], acred->cred->group_info->gid[i]))
			return 0;
	return 1;
}