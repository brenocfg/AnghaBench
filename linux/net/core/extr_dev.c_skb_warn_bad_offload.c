#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* sk; struct net_device* dev; } ;
struct TYPE_4__ {scalar_t__ parent; } ;
struct net_device {int /*<<< orphan*/  const features; TYPE_2__ dev; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_3__ {int /*<<< orphan*/  const sk_route_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  WARN (int,char*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 char* dev_driver_string (scalar_t__) ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 char* netdev_name (struct net_device*) ; 
 int /*<<< orphan*/  skb_dump (int /*<<< orphan*/ ,struct sk_buff const*,int) ; 

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
	skb_dump(KERN_WARNING, skb, false);
	WARN(1, "%s: caps=(%pNF, %pNF)\n",
	     name, dev ? &dev->features : &null_features,
	     skb->sk ? &skb->sk->sk_route_caps : &null_features);
}