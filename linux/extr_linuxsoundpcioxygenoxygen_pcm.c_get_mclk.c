#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {unsigned int dac_mclks; unsigned int adc_mclks; } ;
struct oxygen {TYPE_1__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_I2S_MCLK (unsigned int) ; 
 unsigned int PCM_MULTICH ; 
 int params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static u16 get_mclk(struct oxygen *chip, unsigned int channel,
		    struct snd_pcm_hw_params *params)
{
	unsigned int mclks, shift;

	if (channel == PCM_MULTICH)
		mclks = chip->model.dac_mclks;
	else
		mclks = chip->model.adc_mclks;

	if (params_rate(params) <= 48000)
		shift = 0;
	else if (params_rate(params) <= 96000)
		shift = 2;
	else
		shift = 4;

	return OXYGEN_I2S_MCLK(mclks >> shift);
}