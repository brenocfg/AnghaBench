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
 unsigned int SND_SOC_DAIFMT_I2S ; 
 unsigned int SND_SOC_DAIFMT_IB_IF ; 
 unsigned int SND_SOC_DAIFMT_NB_IF ; 

__attribute__((used)) static inline bool axg_tdm_lrclk_invert(unsigned int fmt)
{
	return (fmt & SND_SOC_DAIFMT_I2S) ^
		!!(fmt & (SND_SOC_DAIFMT_IB_IF | SND_SOC_DAIFMT_NB_IF));
}