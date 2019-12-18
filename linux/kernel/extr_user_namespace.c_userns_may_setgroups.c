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
struct TYPE_2__ {scalar_t__ nr_extents; } ;
struct user_namespace {int flags; TYPE_1__ gid_map; } ;

/* Variables and functions */
 int USERNS_SETGROUPS_ALLOWED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userns_state_mutex ; 

bool userns_may_setgroups(const struct user_namespace *ns)
{
	bool allowed;

	mutex_lock(&userns_state_mutex);
	/* It is not safe to use setgroups until a gid mapping in
	 * the user namespace has been established.
	 */
	allowed = ns->gid_map.nr_extents != 0;
	/* Is setgroups allowed? */
	allowed = allowed && (ns->flags & USERNS_SETGROUPS_ALLOWED);
	mutex_unlock(&userns_state_mutex);

	return allowed;
}