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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_vde {scalar_t__ bsev; } ;

/* Variables and functions */
 scalar_t__ ICMDQUE_WR ; 
 int /*<<< orphan*/  VDE_WR (int /*<<< orphan*/ ,scalar_t__) ; 
 int tegra_vde_wait_bsev (struct tegra_vde*,int) ; 

__attribute__((used)) static int tegra_vde_push_to_bsev_icmdqueue(struct tegra_vde *vde,
					    u32 value, bool wait_dma)
{
	VDE_WR(value, vde->bsev + ICMDQUE_WR);

	return tegra_vde_wait_bsev(vde, wait_dma);
}