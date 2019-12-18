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
typedef  unsigned int u32 ;
struct img_spdif_in {unsigned int single_freq; int /*<<< orphan*/  lock; scalar_t__ active; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IMG_SPDIF_IN_CLKGEN ; 
 unsigned int IMG_SPDIF_IN_CLKGEN_HLD_MASK ; 
 unsigned int IMG_SPDIF_IN_CLKGEN_HLD_SHIFT ; 
 unsigned int IMG_SPDIF_IN_CLKGEN_NOM_MASK ; 
 unsigned int IMG_SPDIF_IN_CLKGEN_NOM_SHIFT ; 
 int img_spdif_in_check_max_rate (struct img_spdif_in*,unsigned int,unsigned long*) ; 
 int img_spdif_in_do_clkgen_calc (unsigned int,unsigned int*,unsigned int*,unsigned long) ; 
 int /*<<< orphan*/  img_spdif_in_writel (struct img_spdif_in*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_in_do_clkgen_single(struct img_spdif_in *spdif,
		unsigned int rate)
{
	unsigned int nom, hld;
	unsigned long flags, clk_rate;
	int ret = 0;
	u32 reg;

	ret = img_spdif_in_check_max_rate(spdif, rate, &clk_rate);
	if (ret)
		return ret;

	ret = img_spdif_in_do_clkgen_calc(rate, &nom, &hld, clk_rate);
	if (ret)
		return ret;

	reg = (nom << IMG_SPDIF_IN_CLKGEN_NOM_SHIFT) &
		IMG_SPDIF_IN_CLKGEN_NOM_MASK;
	reg |= (hld << IMG_SPDIF_IN_CLKGEN_HLD_SHIFT) &
		IMG_SPDIF_IN_CLKGEN_HLD_MASK;

	spin_lock_irqsave(&spdif->lock, flags);

	if (spdif->active) {
		spin_unlock_irqrestore(&spdif->lock, flags);
		return -EBUSY;
	}

	img_spdif_in_writel(spdif, reg, IMG_SPDIF_IN_CLKGEN);

	spdif->single_freq = rate;

	spin_unlock_irqrestore(&spdif->lock, flags);

	return 0;
}