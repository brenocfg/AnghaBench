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
struct group_info {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int commit_creds (struct cred*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  set_groups (struct cred*,struct group_info*) ; 

int set_current_groups(struct group_info *group_info)
{
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	set_groups(new, group_info);
	return commit_creds(new);
}