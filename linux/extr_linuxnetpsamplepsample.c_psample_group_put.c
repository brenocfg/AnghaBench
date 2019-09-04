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
struct psample_group {scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  psample_group_destroy (struct psample_group*) ; 
 int /*<<< orphan*/  psample_groups_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void psample_group_put(struct psample_group *group)
{
	spin_lock(&psample_groups_lock);

	if (--group->refcount == 0)
		psample_group_destroy(group);

	spin_unlock(&psample_groups_lock);
}