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
struct fsnotify_group {int /*<<< orphan*/  memcg; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_group_priv ) (struct fsnotify_group*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fsnotify_group*) ; 
 int /*<<< orphan*/  mem_cgroup_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fsnotify_group*) ; 

__attribute__((used)) static void fsnotify_final_destroy_group(struct fsnotify_group *group)
{
	if (group->ops->free_group_priv)
		group->ops->free_group_priv(group);

	mem_cgroup_put(group->memcg);

	kfree(group);
}