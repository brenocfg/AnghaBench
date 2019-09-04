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
 unsigned int PCM1789_DAC_VOL_RIGHT ; 
 unsigned int PCM1789_MUTE_CONTROL ; 

__attribute__((used)) static bool pcm1789_accessible_reg(struct device *dev, unsigned int reg)
{
	return reg >= PCM1789_MUTE_CONTROL && reg <= PCM1789_DAC_VOL_RIGHT;
}