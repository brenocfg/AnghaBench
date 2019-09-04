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
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 unsigned long pch_udc_readl (struct pch_udc_dev*,unsigned long) ; 
 int /*<<< orphan*/  pch_udc_writel (struct pch_udc_dev*,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void pch_udc_bit_set(struct pch_udc_dev *dev,
				     unsigned long reg,
				     unsigned long bitmask)
{
	pch_udc_writel(dev, pch_udc_readl(dev, reg) | bitmask, reg);
}