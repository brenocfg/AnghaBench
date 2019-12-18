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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct hi6210_i2s {unsigned int format; int master; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct hi6210_i2s* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6210_i2s_set_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	struct hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);

	/*
	 * We don't actually set the hardware until the hw_params
	 * call, but we need to validate the user input here.
	 */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	default:
		return -EINVAL;
	}

	i2s->format = fmt;
	i2s->master = (i2s->format & SND_SOC_DAIFMT_MASTER_MASK) ==
		      SND_SOC_DAIFMT_CBS_CFS;

	return 0;
}