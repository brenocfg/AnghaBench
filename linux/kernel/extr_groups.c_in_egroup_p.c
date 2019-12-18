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
struct cred {int /*<<< orphan*/  group_info; int /*<<< orphan*/  egid; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int groups_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int in_egroup_p(kgid_t grp)
{
	const struct cred *cred = current_cred();
	int retval = 1;

	if (!gid_eq(grp, cred->egid))
		retval = groups_search(cred->group_info, grp);
	return retval;
}