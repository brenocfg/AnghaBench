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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MICB_DISABLE ; 
 int /*<<< orphan*/  MICB_ENABLE ; 
 int MIC_BIAS_1 ; 
 int MIC_BIAS_2 ; 
 int MIC_BIAS_3 ; 
 int MIC_BIAS_4 ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 scalar_t__ strnstr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wcd9335_micbias_control (struct snd_soc_component*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __wcd9335_codec_enable_micbias(struct snd_soc_dapm_widget *w,
					int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	int micb_num;

	if (strnstr(w->name, "MIC BIAS1", sizeof("MIC BIAS1")))
		micb_num = MIC_BIAS_1;
	else if (strnstr(w->name, "MIC BIAS2", sizeof("MIC BIAS2")))
		micb_num = MIC_BIAS_2;
	else if (strnstr(w->name, "MIC BIAS3", sizeof("MIC BIAS3")))
		micb_num = MIC_BIAS_3;
	else if (strnstr(w->name, "MIC BIAS4", sizeof("MIC BIAS4")))
		micb_num = MIC_BIAS_4;
	else
		return -EINVAL;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/*
		 * MIC BIAS can also be requested by MBHC,
		 * so use ref count to handle micbias pullup
		 * and enable requests
		 */
		wcd9335_micbias_control(comp, micb_num, MICB_ENABLE, true);
		break;
	case SND_SOC_DAPM_POST_PMU:
		/* wait for cnp time */
		usleep_range(1000, 1100);
		break;
	case SND_SOC_DAPM_POST_PMD:
		wcd9335_micbias_control(comp, micb_num, MICB_DISABLE, true);
		break;
	};

	return 0;
}