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
 size_t PHY_TYPE_PCS ; 
 size_t PHY_TYPE_PMA_PMD ; 

__attribute__((used)) static int port_has_10g(struct phy_probe_info *p, int port)
{
	int i;

	for (i = 0; i < p->cur[PHY_TYPE_PMA_PMD]; i++) {
		if (p->phy_port[PHY_TYPE_PMA_PMD][i] == port)
			return 1;
	}
	for (i = 0; i < p->cur[PHY_TYPE_PCS]; i++) {
		if (p->phy_port[PHY_TYPE_PCS][i] == port)
			return 1;
	}

	return 0;
}