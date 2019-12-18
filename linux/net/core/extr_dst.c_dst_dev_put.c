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
struct dst_entry {struct net_device* dev; int /*<<< orphan*/  output; int /*<<< orphan*/  input; TYPE_1__* ops; int /*<<< orphan*/  obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ifdown ) (struct dst_entry*,struct net_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DST_OBSOLETE_DEAD ; 
 struct net_device* blackhole_netdev ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dst_discard ; 
 int /*<<< orphan*/  dst_discard_out ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct net_device*,int) ; 

void dst_dev_put(struct dst_entry *dst)
{
	struct net_device *dev = dst->dev;

	dst->obsolete = DST_OBSOLETE_DEAD;
	if (dst->ops->ifdown)
		dst->ops->ifdown(dst, dev, true);
	dst->input = dst_discard;
	dst->output = dst_discard_out;
	dst->dev = blackhole_netdev;
	dev_hold(dst->dev);
	dev_put(dev);
}