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
struct tomoyo_policy_namespace {int profile_version; int /*<<< orphan*/  namespace_list; int /*<<< orphan*/ * policy_list; int /*<<< orphan*/ * group_list; int /*<<< orphan*/ * acl_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int TOMOYO_MAX_ACL_GROUPS ; 
 unsigned int TOMOYO_MAX_GROUP ; 
 unsigned int TOMOYO_MAX_POLICY ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int tomoyo_namespace_enabled ; 
 int /*<<< orphan*/  tomoyo_namespace_list ; 

void tomoyo_init_policy_namespace(struct tomoyo_policy_namespace *ns)
{
	unsigned int idx;

	for (idx = 0; idx < TOMOYO_MAX_ACL_GROUPS; idx++)
		INIT_LIST_HEAD(&ns->acl_group[idx]);
	for (idx = 0; idx < TOMOYO_MAX_GROUP; idx++)
		INIT_LIST_HEAD(&ns->group_list[idx]);
	for (idx = 0; idx < TOMOYO_MAX_POLICY; idx++)
		INIT_LIST_HEAD(&ns->policy_list[idx]);
	ns->profile_version = 20150505;
	tomoyo_namespace_enabled = !list_empty(&tomoyo_namespace_list);
	list_add_tail_rcu(&ns->namespace_list, &tomoyo_namespace_list);
}