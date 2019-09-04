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
struct device {int dummy; } ;

/* Variables and functions */
#define  MT6797_MEMIF_DAI 129 
#define  MT6797_MEMIF_MOD_DAI 128 
 unsigned int dai_memif_rate_transform (struct device*,unsigned int) ; 
 unsigned int mt6797_general_rate_transform (struct device*,unsigned int) ; 

unsigned int mt6797_rate_transform(struct device *dev,
				   unsigned int rate, int aud_blk)
{
	switch (aud_blk) {
	case MT6797_MEMIF_DAI:
	case MT6797_MEMIF_MOD_DAI:
		return dai_memif_rate_transform(dev, rate);
	default:
		return mt6797_general_rate_transform(dev, rate);
	}
}