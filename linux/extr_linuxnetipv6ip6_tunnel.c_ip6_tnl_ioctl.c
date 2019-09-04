#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct ip6_tnl_parm {int /*<<< orphan*/  proto; } ;
struct ip6_tnl_net {struct net_device* fb_tnl_dev; } ;
struct ip6_tnl {struct net_device* dev; int /*<<< orphan*/  parms; struct net* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {TYPE_1__ ifr_ifru; } ;
struct __ip6_tnl_parm {int /*<<< orphan*/  proto; } ;
typedef  int /*<<< orphan*/  p1 ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IS_ERR (struct ip6_tnl*) ; 
 int PTR_ERR (struct ip6_tnl*) ; 
#define  SIOCADDTUNNEL 131 
#define  SIOCCHGTUNNEL 130 
#define  SIOCDELTUNNEL 129 
#define  SIOCGETTUNNEL 128 
 int /*<<< orphan*/  copy_from_user (struct ip6_tnl_parm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,struct ip6_tnl_parm*,int) ; 
 int ip6_tnl0_update (struct ip6_tnl*,struct ip6_tnl_parm*) ; 
 struct ip6_tnl* ip6_tnl_locate (struct net*,struct ip6_tnl_parm*,int) ; 
 int /*<<< orphan*/  ip6_tnl_net_id ; 
 int /*<<< orphan*/  ip6_tnl_parm_from_user (struct ip6_tnl_parm*,struct ip6_tnl_parm*) ; 
 int /*<<< orphan*/  ip6_tnl_parm_to_user (struct ip6_tnl_parm*,int /*<<< orphan*/ *) ; 
 int ip6_tnl_update (struct ip6_tnl*,struct ip6_tnl_parm*) ; 
 int /*<<< orphan*/  memset (struct ip6_tnl_parm*,int /*<<< orphan*/ ,int) ; 
 struct ip6_tnl_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int
ip6_tnl_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int err = 0;
	struct ip6_tnl_parm p;
	struct __ip6_tnl_parm p1;
	struct ip6_tnl *t = netdev_priv(dev);
	struct net *net = t->net;
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	memset(&p1, 0, sizeof(p1));

	switch (cmd) {
	case SIOCGETTUNNEL:
		if (dev == ip6n->fb_tnl_dev) {
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p))) {
				err = -EFAULT;
				break;
			}
			ip6_tnl_parm_from_user(&p1, &p);
			t = ip6_tnl_locate(net, &p1, 0);
			if (IS_ERR(t))
				t = netdev_priv(dev);
		} else {
			memset(&p, 0, sizeof(p));
		}
		ip6_tnl_parm_to_user(&p, &t->parms);
		if (copy_to_user(ifr->ifr_ifru.ifru_data, &p, sizeof(p))) {
			err = -EFAULT;
		}
		break;
	case SIOCADDTUNNEL:
	case SIOCCHGTUNNEL:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			break;
		err = -EFAULT;
		if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
			break;
		err = -EINVAL;
		if (p.proto != IPPROTO_IPV6 && p.proto != IPPROTO_IPIP &&
		    p.proto != 0)
			break;
		ip6_tnl_parm_from_user(&p1, &p);
		t = ip6_tnl_locate(net, &p1, cmd == SIOCADDTUNNEL);
		if (cmd == SIOCCHGTUNNEL) {
			if (!IS_ERR(t)) {
				if (t->dev != dev) {
					err = -EEXIST;
					break;
				}
			} else
				t = netdev_priv(dev);
			if (dev == ip6n->fb_tnl_dev)
				err = ip6_tnl0_update(t, &p1);
			else
				err = ip6_tnl_update(t, &p1);
		}
		if (!IS_ERR(t)) {
			err = 0;
			ip6_tnl_parm_to_user(&p, &t->parms);
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &p, sizeof(p)))
				err = -EFAULT;

		} else {
			err = PTR_ERR(t);
		}
		break;
	case SIOCDELTUNNEL:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			break;

		if (dev == ip6n->fb_tnl_dev) {
			err = -EFAULT;
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
				break;
			err = -ENOENT;
			ip6_tnl_parm_from_user(&p1, &p);
			t = ip6_tnl_locate(net, &p1, 0);
			if (IS_ERR(t))
				break;
			err = -EPERM;
			if (t->dev == ip6n->fb_tnl_dev)
				break;
			dev = t->dev;
		}
		err = 0;
		unregister_netdevice(dev);
		break;
	default:
		err = -EINVAL;
	}
	return err;
}