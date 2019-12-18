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
#define  AC97_REC_GAIN 128 
 int regmap_ac97_default_volatile (struct device*,unsigned int) ; 

__attribute__((used)) static bool wm9712_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AC97_REC_GAIN:
		return true;
	default:
		return regmap_ac97_default_volatile(dev, reg);
	}
}