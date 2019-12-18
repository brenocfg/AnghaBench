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
struct cred {TYPE_1__* group_info; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct TYPE_2__ {int ngroups; int /*<<< orphan*/ * gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nfsd_match_cred(const struct cred *c1, const struct cred *c2)
{
	int i;

	if (!uid_eq(c1->fsuid, c2->fsuid))
		return false;
	if (!gid_eq(c1->fsgid, c2->fsgid))
		return false;
	if (c1->group_info == NULL || c2->group_info == NULL)
		return c1->group_info == c2->group_info;
	if (c1->group_info->ngroups != c2->group_info->ngroups)
		return false;
	for (i = 0; i < c1->group_info->ngroups; i++) {
		if (!gid_eq(c1->group_info->gid[i], c2->group_info->gid[i]))
			return false;
	}
	return true;
}