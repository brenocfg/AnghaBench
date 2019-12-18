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
struct ag71xx {int* pllreg; int /*<<< orphan*/  pllregmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath79_set_pllval (struct ag71xx*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ath79_set_pll(struct ag71xx *ag)
{
	u32 pll_cfg = ag->pllreg[0];
	u32 pll_shift = ag->pllreg[2];

	if (!ag->pllregmap)
		return;

	regmap_update_bits(ag->pllregmap, pll_cfg, 3 << pll_shift, 2 << pll_shift);
	udelay(100);

	ath79_set_pllval(ag);

	regmap_update_bits(ag->pllregmap, pll_cfg, 3 << pll_shift, 3 << pll_shift);
	udelay(100);

	regmap_update_bits(ag->pllregmap, pll_cfg, 3 << pll_shift, 0);
	udelay(100);
}