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
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {int int_level; int int_statid; int /*<<< orphan*/  vme_int; int /*<<< orphan*/  int_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fake_irq_generate(struct vme_bridge *fake_bridge, int level,
		int statid)
{
	struct fake_driver *bridge;

	bridge = fake_bridge->driver_priv;

	mutex_lock(&bridge->vme_int);

	bridge->int_level = level;

	bridge->int_statid = statid;

	/*
	 * Schedule tasklet to run VME handler to emulate normal VME interrupt
	 * handler behaviour.
	 */
	tasklet_schedule(&bridge->int_tasklet);

	mutex_unlock(&bridge->vme_int);

	return 0;
}