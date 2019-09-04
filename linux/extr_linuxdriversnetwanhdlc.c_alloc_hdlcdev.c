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
struct hdlc_device {int dummy; } ;
struct TYPE_2__ {void* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_setup ; 

struct net_device *alloc_hdlcdev(void *priv)
{
	struct net_device *dev;
	dev = alloc_netdev(sizeof(struct hdlc_device), "hdlc%d",
			   NET_NAME_UNKNOWN, hdlc_setup);
	if (dev)
		dev_to_hdlc(dev)->priv = priv;
	return dev;
}