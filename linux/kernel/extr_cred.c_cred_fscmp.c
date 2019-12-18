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
struct group_info {int ngroups; int /*<<< orphan*/ * gid; } ;
struct cred {struct group_info* group_info; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 scalar_t__ gid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cred_fscmp(const struct cred *a, const struct cred *b)
{
	struct group_info *ga, *gb;
	int g;

	if (a == b)
		return 0;
	if (uid_lt(a->fsuid, b->fsuid))
		return -1;
	if (uid_gt(a->fsuid, b->fsuid))
		return 1;

	if (gid_lt(a->fsgid, b->fsgid))
		return -1;
	if (gid_gt(a->fsgid, b->fsgid))
		return 1;

	ga = a->group_info;
	gb = b->group_info;
	if (ga == gb)
		return 0;
	if (ga == NULL)
		return -1;
	if (gb == NULL)
		return 1;
	if (ga->ngroups < gb->ngroups)
		return -1;
	if (ga->ngroups > gb->ngroups)
		return 1;

	for (g = 0; g < ga->ngroups; g++) {
		if (gid_lt(ga->gid[g], gb->gid[g]))
			return -1;
		if (gid_gt(ga->gid[g], gb->gid[g]))
			return 1;
	}
	return 0;
}