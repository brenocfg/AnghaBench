#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nau8825 {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int osr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CLK_DA_AD_MAX ; 
 int EINVAL ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* osr_adc_sel ; 
 TYPE_1__* osr_dac_sel ; 

__attribute__((used)) static int nau8825_clock_check(struct nau8825 *nau8825,
	int stream, int rate, int osr)
{
	int osrate;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (osr >= ARRAY_SIZE(osr_dac_sel))
			return -EINVAL;
		osrate = osr_dac_sel[osr].osr;
	} else {
		if (osr >= ARRAY_SIZE(osr_adc_sel))
			return -EINVAL;
		osrate = osr_adc_sel[osr].osr;
	}

	if (!osrate || rate * osr > CLK_DA_AD_MAX) {
		dev_err(nau8825->dev, "exceed the maximum frequency of CLK_ADC or CLK_DAC\n");
		return -EINVAL;
	}

	return 0;
}