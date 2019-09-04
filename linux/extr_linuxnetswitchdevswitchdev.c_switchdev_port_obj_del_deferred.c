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
struct switchdev_obj {int /*<<< orphan*/  complete_priv; int /*<<< orphan*/  (* complete ) (struct net_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int switchdev_port_obj_del_now (struct net_device*,struct switchdev_obj const*) ; 

__attribute__((used)) static void switchdev_port_obj_del_deferred(struct net_device *dev,
					    const void *data)
{
	const struct switchdev_obj *obj = data;
	int err;

	err = switchdev_port_obj_del_now(dev, obj);
	if (err && err != -EOPNOTSUPP)
		netdev_err(dev, "failed (err=%d) to del object (id=%d)\n",
			   err, obj->id);
	if (obj->complete)
		obj->complete(dev, err, obj->complete_priv);
}