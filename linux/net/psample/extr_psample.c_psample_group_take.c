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
struct psample_group {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  psample_groups_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void psample_group_take(struct psample_group *group)
{
	spin_lock_bh(&psample_groups_lock);
	group->refcount++;
	spin_unlock_bh(&psample_groups_lock);
}