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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int AIC32X4_AVDDWEAKDISABLE ; 
 int /*<<< orphan*/  AIC32X4_LDOCTL ; 
 int AIC32X4_LDOCTLEN ; 
 int /*<<< orphan*/  AIC32X4_MICBIAS ; 
 int AIC32X4_MICBIAS_2075V ; 
 int AIC32X4_MICBIAS_LDOIN ; 
 int /*<<< orphan*/  AIC32X4_PWRCFG ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int audiosense_pi_card_init(struct snd_soc_pcm_runtime *rtd)
{
	/* TODO: init of the codec specific dapm data, ignore suspend/resume */
	struct snd_soc_component *component = rtd->codec_dai->component;

	snd_soc_component_update_bits(component, AIC32X4_MICBIAS, 0x78,
				      AIC32X4_MICBIAS_LDOIN |
				      AIC32X4_MICBIAS_2075V);
	snd_soc_component_update_bits(component, AIC32X4_PWRCFG, 0x08,
				      AIC32X4_AVDDWEAKDISABLE);
	snd_soc_component_update_bits(component, AIC32X4_LDOCTL, 0x01,
				      AIC32X4_LDOCTLEN);

	return 0;
}