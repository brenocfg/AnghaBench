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

/* Variables and functions */
 unsigned int KIRKWOOD_PLAYCTL_I2S_EN ; 
 unsigned int KIRKWOOD_PLAYCTL_I2S_MUTE ; 
 unsigned int KIRKWOOD_PLAYCTL_SPDIF_EN ; 
 unsigned int KIRKWOOD_PLAYCTL_SPDIF_MUTE ; 

__attribute__((used)) static unsigned kirkwood_i2s_play_mute(unsigned ctl)
{
	if (!(ctl & KIRKWOOD_PLAYCTL_I2S_EN))
		ctl |= KIRKWOOD_PLAYCTL_I2S_MUTE;
	if (!(ctl & KIRKWOOD_PLAYCTL_SPDIF_EN))
		ctl |= KIRKWOOD_PLAYCTL_SPDIF_MUTE;
	return ctl;
}