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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int mcs7830_get_rev (struct usbnet*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mcs7830_get_regs_len(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);

	switch (mcs7830_get_rev(dev)) {
	case 1:
		return 21;
	case 2:
		return 32;
	}
	return 0;
}