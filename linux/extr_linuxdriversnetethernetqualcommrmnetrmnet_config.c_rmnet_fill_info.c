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
struct sk_buff {int dummy; } ;
struct rmnet_priv {int /*<<< orphan*/  mux_id; struct net_device* real_dev; } ;
struct rmnet_port {scalar_t__ data_format; } ;
struct net_device {int dummy; } ;
struct ifla_rmnet_flags {int /*<<< orphan*/  mask; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  f ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_RMNET_FLAGS ; 
 int /*<<< orphan*/  IFLA_RMNET_MUX_ID ; 
 struct rmnet_priv* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct ifla_rmnet_flags*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rmnet_port* rmnet_get_port_rtnl (struct net_device*) ; 
 scalar_t__ rmnet_is_real_dev_registered (struct net_device*) ; 

__attribute__((used)) static int rmnet_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct rmnet_priv *priv = netdev_priv(dev);
	struct net_device *real_dev;
	struct ifla_rmnet_flags f;
	struct rmnet_port *port;

	real_dev = priv->real_dev;

	if (nla_put_u16(skb, IFLA_RMNET_MUX_ID, priv->mux_id))
		goto nla_put_failure;

	if (rmnet_is_real_dev_registered(real_dev)) {
		port = rmnet_get_port_rtnl(real_dev);
		f.flags = port->data_format;
	} else {
		f.flags = 0;
	}

	f.mask  = ~0;

	if (nla_put(skb, IFLA_RMNET_FLAGS, sizeof(f), &f))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}