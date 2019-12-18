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
struct mr_table {int maxvif; TYPE_1__* vif_table; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */

__attribute__((used)) static int ipmr_find_vif(struct mr_table *mrt, struct net_device *dev)
{
	int ct;

	for (ct = mrt->maxvif-1; ct >= 0; ct--) {
		if (mrt->vif_table[ct].dev == dev)
			break;
	}
	return ct;
}