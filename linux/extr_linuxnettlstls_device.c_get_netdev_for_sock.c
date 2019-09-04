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
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct dst_entry {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ likely (struct dst_entry*) ; 
 struct dst_entry* sk_dst_get (struct sock*) ; 

__attribute__((used)) static struct net_device *get_netdev_for_sock(struct sock *sk)
{
	struct dst_entry *dst = sk_dst_get(sk);
	struct net_device *netdev = NULL;

	if (likely(dst)) {
		netdev = dst->dev;
		dev_hold(netdev);
	}

	dst_release(dst);

	return netdev;
}