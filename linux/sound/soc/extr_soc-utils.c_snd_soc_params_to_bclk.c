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
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

int snd_soc_params_to_bclk(struct snd_pcm_hw_params *params)
{
	int ret;

	ret = snd_soc_params_to_frame_size(params);

	if (ret > 0)
		return ret * params_rate(params);
	else
		return ret;
}