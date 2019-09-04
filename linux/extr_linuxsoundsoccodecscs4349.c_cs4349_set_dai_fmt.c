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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs4349_private {unsigned int mode; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct cs4349_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs4349_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int format)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs4349_private *cs4349 = snd_soc_component_get_drvdata(component);
	unsigned int fmt;

	fmt = format & SND_SOC_DAIFMT_FORMAT_MASK;

	switch (fmt) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		cs4349->mode = format & SND_SOC_DAIFMT_FORMAT_MASK;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}