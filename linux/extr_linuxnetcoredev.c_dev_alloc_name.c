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
 int dev_alloc_name_ns (int /*<<< orphan*/ ,struct net_device*,char const*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 

int dev_alloc_name(struct net_device *dev, const char *name)
{
	return dev_alloc_name_ns(dev_net(dev), dev, name);
}