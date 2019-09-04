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
typedef  int u32 ;
typedef  size_t u16 ;
struct rmnet_port {int rmnet_mode; int data_format; int /*<<< orphan*/ * muxed_ep; } ;
struct rmnet_endpoint {int /*<<< orphan*/  hlnode; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ifla_rmnet_flags {int flags; int mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t IFLA_LINK ; 
 size_t IFLA_RMNET_FLAGS ; 
 size_t IFLA_RMNET_MUX_ID ; 
 int RMNET_EPMODE_VND ; 
 int RMNET_FLAGS_INGRESS_DEAGGREGATION ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rmnet_endpoint*) ; 
 struct rmnet_endpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct ifla_rmnet_flags* nla_data (struct nlattr*) ; 
 size_t nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct rmnet_port* rmnet_get_port_rtnl (struct net_device*) ; 
 int rmnet_register_real_device (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_unregister_real_device (struct net_device*,struct rmnet_port*) ; 
 int rmnet_vnd_newlink (size_t,struct net_device*,struct rmnet_port*,struct net_device*,struct rmnet_endpoint*) ; 

__attribute__((used)) static int rmnet_newlink(struct net *src_net, struct net_device *dev,
			 struct nlattr *tb[], struct nlattr *data[],
			 struct netlink_ext_ack *extack)
{
	u32 data_format = RMNET_FLAGS_INGRESS_DEAGGREGATION;
	struct net_device *real_dev;
	int mode = RMNET_EPMODE_VND;
	struct rmnet_endpoint *ep;
	struct rmnet_port *port;
	int err = 0;
	u16 mux_id;

	real_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (!real_dev || !dev)
		return -ENODEV;

	if (!data[IFLA_RMNET_MUX_ID])
		return -EINVAL;

	ep = kzalloc(sizeof(*ep), GFP_ATOMIC);
	if (!ep)
		return -ENOMEM;

	mux_id = nla_get_u16(data[IFLA_RMNET_MUX_ID]);

	err = rmnet_register_real_device(real_dev);
	if (err)
		goto err0;

	port = rmnet_get_port_rtnl(real_dev);
	err = rmnet_vnd_newlink(mux_id, dev, port, real_dev, ep);
	if (err)
		goto err1;

	port->rmnet_mode = mode;

	hlist_add_head_rcu(&ep->hlnode, &port->muxed_ep[mux_id]);

	if (data[IFLA_RMNET_FLAGS]) {
		struct ifla_rmnet_flags *flags;

		flags = nla_data(data[IFLA_RMNET_FLAGS]);
		data_format = flags->flags & flags->mask;
	}

	netdev_dbg(dev, "data format [0x%08X]\n", data_format);
	port->data_format = data_format;

	return 0;

err1:
	rmnet_unregister_real_device(real_dev, port);
err0:
	kfree(ep);
	return err;
}