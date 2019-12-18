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
struct devlink_trap {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_trap_disable (struct devlink*,struct devlink_trap const*) ; 
 int /*<<< orphan*/  devlink_trap_unregister (struct devlink*,struct devlink_trap const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void devlink_traps_unregister(struct devlink *devlink,
			      const struct devlink_trap *traps,
			      size_t traps_count)
{
	int i;

	mutex_lock(&devlink->lock);
	/* Make sure we do not have any packets in-flight while unregistering
	 * traps by disabling all of them and waiting for a grace period.
	 */
	for (i = traps_count - 1; i >= 0; i--)
		devlink_trap_disable(devlink, &traps[i]);
	synchronize_rcu();
	for (i = traps_count - 1; i >= 0; i--)
		devlink_trap_unregister(devlink, &traps[i]);
	mutex_unlock(&devlink->lock);
}