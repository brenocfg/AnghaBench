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
struct psample_group {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSAMPLE_CMD_DEL_GROUP ; 
 int /*<<< orphan*/  kfree_rcu (struct psample_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psample_group_notify (struct psample_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void psample_group_destroy(struct psample_group *group)
{
	psample_group_notify(group, PSAMPLE_CMD_DEL_GROUP);
	list_del(&group->list);
	kfree_rcu(group, rcu);
}