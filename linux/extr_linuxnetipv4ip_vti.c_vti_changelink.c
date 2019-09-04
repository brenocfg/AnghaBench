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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct ip_tunnel_parm {int dummy; } ;
struct ip_tunnel {int /*<<< orphan*/  fwmark; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ip_tunnel_changelink (struct net_device*,struct nlattr**,struct ip_tunnel_parm*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vti_netlink_parms (struct nlattr**,struct ip_tunnel_parm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vti_changelink(struct net_device *dev, struct nlattr *tb[],
			  struct nlattr *data[],
			  struct netlink_ext_ack *extack)
{
	struct ip_tunnel *t = netdev_priv(dev);
	__u32 fwmark = t->fwmark;
	struct ip_tunnel_parm p;

	vti_netlink_parms(data, &p, &fwmark);
	return ip_tunnel_changelink(dev, tb, &p, fwmark);
}