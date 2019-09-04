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
struct phy_probe_info {int* cur; int** phy_port; } ;

/* Variables and functions */
 size_t PHY_TYPE_MII ; 

__attribute__((used)) static int count_1g_ports(struct phy_probe_info *p, int *lowest)
{
	*lowest = 32;
	if (p->cur[PHY_TYPE_MII])
		*lowest = p->phy_port[PHY_TYPE_MII][0];

	return p->cur[PHY_TYPE_MII];
}