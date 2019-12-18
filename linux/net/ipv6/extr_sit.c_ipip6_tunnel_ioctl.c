#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sit_net {struct net_device* fb_tunnel_dev; } ;
struct net_device {int flags; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct TYPE_5__ {int version; int ihl; int frag_off; int /*<<< orphan*/  daddr; int /*<<< orphan*/  ttl; int /*<<< orphan*/  protocol; } ;
struct ip_tunnel_prl {TYPE_2__ iph; int /*<<< orphan*/  relay_prefixlen; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  relay_prefix; int /*<<< orphan*/  prefix; } ;
struct ip_tunnel_parm {TYPE_2__ iph; int /*<<< orphan*/  relay_prefixlen; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  relay_prefix; int /*<<< orphan*/  prefix; } ;
struct ip_tunnel_6rd {TYPE_2__ iph; int /*<<< orphan*/  relay_prefixlen; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  relay_prefix; int /*<<< orphan*/  prefix; } ;
struct TYPE_4__ {int /*<<< orphan*/  relay_prefixlen; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  relay_prefix; int /*<<< orphan*/  prefix; } ;
struct ip_tunnel {int /*<<< orphan*/  dst_cache; struct net_device* dev; struct ip_tunnel_prl parms; int /*<<< orphan*/  fwmark; TYPE_1__ ip6rd; struct net* net; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {TYPE_3__ ifr_ifru; } ;
typedef  int /*<<< orphan*/  prl ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  ip6rd ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int EPERM ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IP_DF ; 
#define  SIOCADD6RD 139 
#define  SIOCADDPRL 138 
#define  SIOCADDTUNNEL 137 
#define  SIOCCHG6RD 136 
#define  SIOCCHGPRL 135 
#define  SIOCCHGTUNNEL 134 
#define  SIOCDEL6RD 133 
#define  SIOCDELPRL 132 
#define  SIOCDELTUNNEL 131 
#define  SIOCGET6RD 130 
#define  SIOCGETPRL 129 
#define  SIOCGETTUNNEL 128 
 int /*<<< orphan*/  copy_from_user (struct ip_tunnel_prl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,struct ip_tunnel_prl*,int) ; 
 int /*<<< orphan*/  dst_cache_reset (int /*<<< orphan*/ *) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int ipip6_tunnel_add_prl (struct ip_tunnel*,struct ip_tunnel_prl*,int) ; 
 int /*<<< orphan*/  ipip6_tunnel_clone_6rd (struct net_device*,struct sit_net*) ; 
 int ipip6_tunnel_del_prl (struct ip_tunnel*,struct ip_tunnel_prl*) ; 
 int ipip6_tunnel_get_prl (struct ip_tunnel*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* ipip6_tunnel_locate (struct net*,struct ip_tunnel_prl*,int) ; 
 int /*<<< orphan*/  ipip6_tunnel_update (struct ip_tunnel*,struct ip_tunnel_prl*,int /*<<< orphan*/ ) ; 
 int ipip6_tunnel_update_6rd (struct ip_tunnel*,struct ip_tunnel_prl*) ; 
 int /*<<< orphan*/  ipip6_valid_ip_proto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ip_tunnel_prl*,struct ip_tunnel_prl*,int) ; 
 struct sit_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sit_net_id ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int
ipip6_tunnel_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int err = 0;
	struct ip_tunnel_parm p;
	struct ip_tunnel_prl prl;
	struct ip_tunnel *t = netdev_priv(dev);
	struct net *net = t->net;
	struct sit_net *sitn = net_generic(net, sit_net_id);
#ifdef CONFIG_IPV6_SIT_6RD
	struct ip_tunnel_6rd ip6rd;
#endif

	switch (cmd) {
	case SIOCGETTUNNEL:
#ifdef CONFIG_IPV6_SIT_6RD
	case SIOCGET6RD:
#endif
		if (dev == sitn->fb_tunnel_dev) {
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p))) {
				err = -EFAULT;
				break;
			}
			t = ipip6_tunnel_locate(net, &p, 0);
			if (!t)
				t = netdev_priv(dev);
		}

		err = -EFAULT;
		if (cmd == SIOCGETTUNNEL) {
			memcpy(&p, &t->parms, sizeof(p));
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &p,
					 sizeof(p)))
				goto done;
#ifdef CONFIG_IPV6_SIT_6RD
		} else {
			ip6rd.prefix = t->ip6rd.prefix;
			ip6rd.relay_prefix = t->ip6rd.relay_prefix;
			ip6rd.prefixlen = t->ip6rd.prefixlen;
			ip6rd.relay_prefixlen = t->ip6rd.relay_prefixlen;
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &ip6rd,
					 sizeof(ip6rd)))
				goto done;
#endif
		}
		err = 0;
		break;

	case SIOCADDTUNNEL:
	case SIOCCHGTUNNEL:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			goto done;

		err = -EFAULT;
		if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
			goto done;

		err = -EINVAL;
		if (!ipip6_valid_ip_proto(p.iph.protocol))
			goto done;
		if (p.iph.version != 4 ||
		    p.iph.ihl != 5 || (p.iph.frag_off&htons(~IP_DF)))
			goto done;
		if (p.iph.ttl)
			p.iph.frag_off |= htons(IP_DF);

		t = ipip6_tunnel_locate(net, &p, cmd == SIOCADDTUNNEL);

		if (dev != sitn->fb_tunnel_dev && cmd == SIOCCHGTUNNEL) {
			if (t) {
				if (t->dev != dev) {
					err = -EEXIST;
					break;
				}
			} else {
				if (((dev->flags&IFF_POINTOPOINT) && !p.iph.daddr) ||
				    (!(dev->flags&IFF_POINTOPOINT) && p.iph.daddr)) {
					err = -EINVAL;
					break;
				}
				t = netdev_priv(dev);
			}

			ipip6_tunnel_update(t, &p, t->fwmark);
		}

		if (t) {
			err = 0;
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &t->parms, sizeof(p)))
				err = -EFAULT;
		} else
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		break;

	case SIOCDELTUNNEL:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			goto done;

		if (dev == sitn->fb_tunnel_dev) {
			err = -EFAULT;
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
				goto done;
			err = -ENOENT;
			t = ipip6_tunnel_locate(net, &p, 0);
			if (!t)
				goto done;
			err = -EPERM;
			if (t == netdev_priv(sitn->fb_tunnel_dev))
				goto done;
			dev = t->dev;
		}
		unregister_netdevice(dev);
		err = 0;
		break;

	case SIOCGETPRL:
		err = -EINVAL;
		if (dev == sitn->fb_tunnel_dev)
			goto done;
		err = ipip6_tunnel_get_prl(t, ifr->ifr_ifru.ifru_data);
		break;

	case SIOCADDPRL:
	case SIOCDELPRL:
	case SIOCCHGPRL:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			goto done;
		err = -EINVAL;
		if (dev == sitn->fb_tunnel_dev)
			goto done;
		err = -EFAULT;
		if (copy_from_user(&prl, ifr->ifr_ifru.ifru_data, sizeof(prl)))
			goto done;

		switch (cmd) {
		case SIOCDELPRL:
			err = ipip6_tunnel_del_prl(t, &prl);
			break;
		case SIOCADDPRL:
		case SIOCCHGPRL:
			err = ipip6_tunnel_add_prl(t, &prl, cmd == SIOCCHGPRL);
			break;
		}
		dst_cache_reset(&t->dst_cache);
		netdev_state_change(dev);
		break;

#ifdef CONFIG_IPV6_SIT_6RD
	case SIOCADD6RD:
	case SIOCCHG6RD:
	case SIOCDEL6RD:
		err = -EPERM;
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			goto done;

		err = -EFAULT;
		if (copy_from_user(&ip6rd, ifr->ifr_ifru.ifru_data,
				   sizeof(ip6rd)))
			goto done;

		if (cmd != SIOCDEL6RD) {
			err = ipip6_tunnel_update_6rd(t, &ip6rd);
			if (err < 0)
				goto done;
		} else
			ipip6_tunnel_clone_6rd(dev, sitn);

		err = 0;
		break;
#endif

	default:
		err = -EINVAL;
	}

done:
	return err;
}