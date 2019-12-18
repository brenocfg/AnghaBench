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
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  INNO_R06 ; 
 int /*<<< orphan*/  INNO_R06_DAC_DISCHARGE ; 
 int /*<<< orphan*/  INNO_R06_DAC_PRECHARGE ; 
 int /*<<< orphan*/  INNO_R10 ; 
 int /*<<< orphan*/  INNO_R10_MAX_CUR ; 
#define  SND_SOC_BIAS_OFF 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3036_codec_set_bias_level(struct snd_soc_component *component,
				       enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_STANDBY:
		/* set a big current for capacitor charging. */
		snd_soc_component_write(component, INNO_R10, INNO_R10_MAX_CUR);
		/* start precharge */
		snd_soc_component_write(component, INNO_R06, INNO_R06_DAC_PRECHARGE);

		break;

	case SND_SOC_BIAS_OFF:
		/* set a big current for capacitor discharging. */
		snd_soc_component_write(component, INNO_R10, INNO_R10_MAX_CUR);
		/* start discharge. */
		snd_soc_component_write(component, INNO_R06, INNO_R06_DAC_DISCHARGE);

		break;
	default:
		break;
	}

	return 0;
}