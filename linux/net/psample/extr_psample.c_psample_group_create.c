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
typedef  int /*<<< orphan*/  u32 ;
struct psample_group {int /*<<< orphan*/  list; int /*<<< orphan*/  group_num; struct net* net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PSAMPLE_CMD_NEW_GROUP ; 
 struct psample_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psample_group_notify (struct psample_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psample_groups_list ; 

__attribute__((used)) static struct psample_group *psample_group_create(struct net *net,
						  u32 group_num)
{
	struct psample_group *group;

	group = kzalloc(sizeof(*group), GFP_ATOMIC);
	if (!group)
		return NULL;

	group->net = net;
	group->group_num = group_num;
	list_add_tail(&group->list, &psample_groups_list);

	psample_group_notify(group, PSAMPLE_CMD_NEW_GROUP);
	return group;
}