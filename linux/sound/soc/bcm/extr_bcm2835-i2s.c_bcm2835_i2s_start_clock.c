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
struct bcm2835_i2s_dev {unsigned int fmt; int clk_prepared; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
#define  SND_SOC_DAIFMT_CBS_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_i2s_start_clock(struct bcm2835_i2s_dev *dev)
{
	unsigned int master = dev->fmt & SND_SOC_DAIFMT_MASTER_MASK;

	if (dev->clk_prepared)
		return;

	switch (master) {
	case SND_SOC_DAIFMT_CBS_CFS:
	case SND_SOC_DAIFMT_CBS_CFM:
		clk_prepare_enable(dev->clk);
		dev->clk_prepared = true;
		break;
	default:
		break;
	}
}