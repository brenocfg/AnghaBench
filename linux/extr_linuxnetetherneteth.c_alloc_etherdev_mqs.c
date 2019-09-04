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

/* Variables and functions */
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev_mqs (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ether_setup ; 

struct net_device *alloc_etherdev_mqs(int sizeof_priv, unsigned int txqs,
				      unsigned int rxqs)
{
	return alloc_netdev_mqs(sizeof_priv, "eth%d", NET_NAME_UNKNOWN,
				ether_setup, txqs, rxqs);
}