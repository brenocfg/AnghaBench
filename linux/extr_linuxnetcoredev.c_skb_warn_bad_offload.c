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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; TYPE_2__* sk; struct net_device* dev; } ;
struct TYPE_4__ {scalar_t__ parent; } ;
struct net_device {int /*<<< orphan*/  const features; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_6__ {int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  const sk_route_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dev_driver_string (scalar_t__) ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 char* netdev_name (struct net_device*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static void skb_warn_bad_offload(const struct sk_buff *skb)
{
	static const netdev_features_t null_features;
	struct net_device *dev = skb->dev;
	const char *name = "";

	if (!net_ratelimit())
		return;

	if (dev) {
		if (dev->dev.parent)
			name = dev_driver_string(dev->dev.parent);
		else
			name = netdev_name(dev);
	}
	WARN(1, "%s: caps=(%pNF, %pNF) len=%d data_len=%d gso_size=%d "
	     "gso_type=%d ip_summed=%d\n",
	     name, dev ? &dev->features : &null_features,
	     skb->sk ? &skb->sk->sk_route_caps : &null_features,
	     skb->len, skb->data_len, skb_shinfo(skb)->gso_size,
	     skb_shinfo(skb)->gso_type, skb->ip_summed);
}