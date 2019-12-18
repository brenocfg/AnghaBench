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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tb ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel {int collect_md; } ;

/* Variables and functions */
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 int /*<<< orphan*/  IP_MAX_MTU ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int __ip_tunnel_change_mtu (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ip_tunnel_dellink (struct net_device*,int /*<<< orphan*/ *) ; 
 int ipgre_newlink (struct net*,struct net_device*,struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipgre_tap_ops ; 
 int /*<<< orphan*/  list_kill ; 
 int /*<<< orphan*/  memset (struct nlattr***,int /*<<< orphan*/ ,int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int rtnl_configure_link (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* rtnl_create_link (struct net*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nlattr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_many (int /*<<< orphan*/ *) ; 

struct net_device *gretap_fb_dev_create(struct net *net, const char *name,
					u8 name_assign_type)
{
	struct nlattr *tb[IFLA_MAX + 1];
	struct net_device *dev;
	LIST_HEAD(list_kill);
	struct ip_tunnel *t;
	int err;

	memset(&tb, 0, sizeof(tb));

	dev = rtnl_create_link(net, name, name_assign_type,
			       &ipgre_tap_ops, tb, NULL);
	if (IS_ERR(dev))
		return dev;

	/* Configure flow based GRE device. */
	t = netdev_priv(dev);
	t->collect_md = true;

	err = ipgre_newlink(net, dev, tb, NULL, NULL);
	if (err < 0) {
		free_netdev(dev);
		return ERR_PTR(err);
	}

	/* openvswitch users expect packet sizes to be unrestricted,
	 * so set the largest MTU we can.
	 */
	err = __ip_tunnel_change_mtu(dev, IP_MAX_MTU, false);
	if (err)
		goto out;

	err = rtnl_configure_link(dev, NULL);
	if (err < 0)
		goto out;

	return dev;
out:
	ip_tunnel_dellink(dev, &list_kill);
	unregister_netdevice_many(&list_kill);
	return ERR_PTR(err);
}