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
 int __dev_mc_add (struct net_device*,unsigned char const*,int) ; 

int dev_mc_add_global(struct net_device *dev, const unsigned char *addr)
{
	return __dev_mc_add(dev, addr, true);
}