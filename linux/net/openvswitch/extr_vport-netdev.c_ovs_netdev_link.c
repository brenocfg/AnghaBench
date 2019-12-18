#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vport {TYPE_1__* dev; int /*<<< orphan*/  dp; } ;
struct TYPE_9__ {int flags; scalar_t__ type; int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_NONE ; 
 int EINVAL ; 
 int ENODEV ; 
 struct vport* ERR_PTR (int) ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFF_OVS_DATAPATH ; 
 int /*<<< orphan*/  dev_disable_lro (TYPE_1__*) ; 
 TYPE_1__* dev_get_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dev_put (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_dpdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_frame_hook ; 
 int netdev_master_upper_dev_link (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int netdev_rx_handler_register (TYPE_1__*,int /*<<< orphan*/ ,struct vport*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 scalar_t__ ovs_is_internal_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

struct vport *ovs_netdev_link(struct vport *vport, const char *name)
{
	int err;

	vport->dev = dev_get_by_name(ovs_dp_get_net(vport->dp), name);
	if (!vport->dev) {
		err = -ENODEV;
		goto error_free_vport;
	}

	if (vport->dev->flags & IFF_LOOPBACK ||
	    (vport->dev->type != ARPHRD_ETHER &&
	     vport->dev->type != ARPHRD_NONE) ||
	    ovs_is_internal_dev(vport->dev)) {
		err = -EINVAL;
		goto error_put;
	}

	rtnl_lock();
	err = netdev_master_upper_dev_link(vport->dev,
					   get_dpdev(vport->dp),
					   NULL, NULL, NULL);
	if (err)
		goto error_unlock;

	err = netdev_rx_handler_register(vport->dev, netdev_frame_hook,
					 vport);
	if (err)
		goto error_master_upper_dev_unlink;

	dev_disable_lro(vport->dev);
	dev_set_promiscuity(vport->dev, 1);
	vport->dev->priv_flags |= IFF_OVS_DATAPATH;
	rtnl_unlock();

	return vport;

error_master_upper_dev_unlink:
	netdev_upper_dev_unlink(vport->dev, get_dpdev(vport->dp));
error_unlock:
	rtnl_unlock();
error_put:
	dev_put(vport->dev);
error_free_vport:
	ovs_vport_free(vport);
	return ERR_PTR(err);
}