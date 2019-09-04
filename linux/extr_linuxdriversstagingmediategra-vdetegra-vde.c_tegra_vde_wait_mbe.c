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
typedef  int u32 ;
struct tegra_vde {scalar_t__ mbe; } ;

/* Variables and functions */
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int tegra_vde_wait_mbe(struct tegra_vde *vde)
{
	u32 tmp;

	return readl_relaxed_poll_timeout(vde->mbe + 0x8C, tmp,
					  (tmp >= 0x10), 1, 100);
}