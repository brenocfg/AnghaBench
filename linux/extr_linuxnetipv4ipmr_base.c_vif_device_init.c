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
struct vif_device {unsigned long rate_limit; unsigned short flags; unsigned char threshold; int /*<<< orphan*/  link; scalar_t__ pkt_out; scalar_t__ pkt_in; scalar_t__ bytes_out; scalar_t__ bytes_in; int /*<<< orphan*/ * dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_iflink (struct net_device*) ; 

void vif_device_init(struct vif_device *v,
		     struct net_device *dev,
		     unsigned long rate_limit,
		     unsigned char threshold,
		     unsigned short flags,
		     unsigned short get_iflink_mask)
{
	v->dev = NULL;
	v->bytes_in = 0;
	v->bytes_out = 0;
	v->pkt_in = 0;
	v->pkt_out = 0;
	v->rate_limit = rate_limit;
	v->flags = flags;
	v->threshold = threshold;
	if (v->flags & get_iflink_mask)
		v->link = dev_get_iflink(dev);
	else
		v->link = dev->ifindex;
}