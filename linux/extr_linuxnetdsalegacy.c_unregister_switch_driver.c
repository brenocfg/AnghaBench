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
struct dsa_switch_driver {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_switch_drivers_mutex ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void unregister_switch_driver(struct dsa_switch_driver *drv)
{
	mutex_lock(&dsa_switch_drivers_mutex);
	list_del_init(&drv->list);
	mutex_unlock(&dsa_switch_drivers_mutex);
}