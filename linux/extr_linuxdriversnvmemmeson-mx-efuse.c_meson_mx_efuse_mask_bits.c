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
struct meson_mx_efuse {int base; } ;

/* Variables and functions */
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void meson_mx_efuse_mask_bits(struct meson_mx_efuse *efuse, u32 reg,
				     u32 mask, u32 set)
{
	u32 data;

	data = readl(efuse->base + reg);
	data &= ~mask;
	data |= (set & mask);

	writel(data, efuse->base + reg);
}