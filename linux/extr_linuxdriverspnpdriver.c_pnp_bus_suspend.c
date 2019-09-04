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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int __pnp_bus_suspend (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnp_bus_suspend(struct device *dev)
{
	return __pnp_bus_suspend(dev, PMSG_SUSPEND);
}