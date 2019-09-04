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
 int /*<<< orphan*/  VDE_WR (int,scalar_t__) ; 

__attribute__((used)) static void tegra_vde_mbe_set_0xa_reg(struct tegra_vde *vde, int reg, u32 val)
{
	VDE_WR(0xA0000000 | (reg << 24) | (val & 0xFFFF), vde->mbe + 0x80);
	VDE_WR(0xA0000000 | ((reg + 1) << 24) | (val >> 16), vde->mbe + 0x80);
}