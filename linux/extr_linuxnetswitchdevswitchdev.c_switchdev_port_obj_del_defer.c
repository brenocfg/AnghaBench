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
struct switchdev_obj {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int switchdev_deferred_enqueue (struct net_device*,struct switchdev_obj const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switchdev_obj_size (struct switchdev_obj const*) ; 
 int /*<<< orphan*/  switchdev_port_obj_del_deferred ; 

__attribute__((used)) static int switchdev_port_obj_del_defer(struct net_device *dev,
					const struct switchdev_obj *obj)
{
	return switchdev_deferred_enqueue(dev, obj, switchdev_obj_size(obj),
					  switchdev_port_obj_del_deferred);
}