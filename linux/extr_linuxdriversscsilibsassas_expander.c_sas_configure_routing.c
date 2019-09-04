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
typedef  int /*<<< orphan*/  u8 ;
struct domain_device {scalar_t__ parent; } ;

/* Variables and functions */
 int sas_configure_parent (scalar_t__,struct domain_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sas_configure_routing(struct domain_device *dev, u8 *sas_addr)
{
	if (dev->parent)
		return sas_configure_parent(dev->parent, dev, sas_addr, 1);
	return 0;
}