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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  TLV320AIC23_ACTIVE ; 
 int TLV320AIC23_CLK_OFF ; 
 int TLV320AIC23_DAC_OFF ; 
 int TLV320AIC23_DEVICE_PWR_OFF ; 
 int TLV320AIC23_OSC_OFF ; 
 int /*<<< orphan*/  TLV320AIC23_PWR ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlv320aic23_set_bias_level(struct snd_soc_component *component,
				      enum snd_soc_bias_level level)
{
	u16 reg = snd_soc_component_read32(component, TLV320AIC23_PWR) & 0x17f;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* vref/mid, osc on, dac unmute */
		reg &= ~(TLV320AIC23_DEVICE_PWR_OFF | TLV320AIC23_OSC_OFF | \
			TLV320AIC23_DAC_OFF);
		snd_soc_component_write(component, TLV320AIC23_PWR, reg);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		snd_soc_component_write(component, TLV320AIC23_PWR,
			      reg | TLV320AIC23_CLK_OFF);
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_write(component, TLV320AIC23_ACTIVE, 0x0);
		snd_soc_component_write(component, TLV320AIC23_PWR, 0x1ff);
		break;
	}
	return 0;
}