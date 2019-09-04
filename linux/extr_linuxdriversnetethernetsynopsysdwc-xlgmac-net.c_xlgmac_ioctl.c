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
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int xlgmac_ioctl(struct net_device *netdev,
			struct ifreq *ifreq, int cmd)
{
	if (!netif_running(netdev))
		return -ENODEV;

	return 0;
}