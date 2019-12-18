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
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {int master; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SACR1_AMSL ; 
#define  SND_SOC_DAIFMT_CBM_CFS 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 TYPE_1__ pxa_i2s ; 

__attribute__((used)) static int pxa2xx_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pxa_i2s.fmt = 0;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		pxa_i2s.fmt = SACR1_AMSL;
		break;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		pxa_i2s.master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		pxa_i2s.master = 0;
		break;
	default:
		break;
	}
	return 0;
}