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
struct net_device {int flags; } ;
struct ifmap {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int IFF_UP ; 

__attribute__((used)) static int gdm_lte_set_config(struct net_device *dev, struct ifmap *map)
{
	if (dev->flags & IFF_UP)
		return -EBUSY;
	return 0;
}