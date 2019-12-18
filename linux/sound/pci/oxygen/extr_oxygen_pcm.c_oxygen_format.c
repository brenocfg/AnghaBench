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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 unsigned int OXYGEN_FORMAT_16 ; 
 unsigned int OXYGEN_FORMAT_24 ; 
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 scalar_t__ params_format (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static unsigned int oxygen_format(struct snd_pcm_hw_params *hw_params)
{
	if (params_format(hw_params) == SNDRV_PCM_FORMAT_S32_LE)
		return OXYGEN_FORMAT_24;
	else
		return OXYGEN_FORMAT_16;
}