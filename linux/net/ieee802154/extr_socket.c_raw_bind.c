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
struct sockaddr_ieee802154 {scalar_t__ family; int /*<<< orphan*/  addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct ieee802154_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_IEEE802154 ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  ieee802154_addr_from_sa (struct ieee802154_addr*,int /*<<< orphan*/ *) ; 
 struct net_device* ieee802154_get_dev (int /*<<< orphan*/ ,struct ieee802154_addr*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int raw_bind(struct sock *sk, struct sockaddr *_uaddr, int len)
{
	struct ieee802154_addr addr;
	struct sockaddr_ieee802154 *uaddr = (struct sockaddr_ieee802154 *)_uaddr;
	int err = 0;
	struct net_device *dev = NULL;

	if (len < sizeof(*uaddr))
		return -EINVAL;

	uaddr = (struct sockaddr_ieee802154 *)_uaddr;
	if (uaddr->family != AF_IEEE802154)
		return -EINVAL;

	lock_sock(sk);

	ieee802154_addr_from_sa(&addr, &uaddr->addr);
	dev = ieee802154_get_dev(sock_net(sk), &addr);
	if (!dev) {
		err = -ENODEV;
		goto out;
	}

	sk->sk_bound_dev_if = dev->ifindex;
	sk_dst_reset(sk);

	dev_put(dev);
out:
	release_sock(sk);

	return err;
}