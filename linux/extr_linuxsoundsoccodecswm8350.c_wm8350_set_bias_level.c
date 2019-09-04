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
typedef  int u16 ;
struct wm8350_data {int /*<<< orphan*/  supplies; struct wm8350* wm8350; } ;
struct wm8350_audio_platform_data {int codec_current_on; int dis_out1; int dis_out2; int dis_out3; int dis_out4; int vmid_s_curve; int codec_current_charge; int codec_current_standby; int /*<<< orphan*/  drain_msecs; int /*<<< orphan*/  vmid_discharge_msecs; int /*<<< orphan*/  vmid_charge_msecs; int /*<<< orphan*/  cap_discharge_msecs; } ;
struct TYPE_2__ {struct wm8350_audio_platform_data* platform_data; } ;
struct wm8350 {TYPE_1__ codec; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8350_ANTI_POP_CONTROL ; 
 int WM8350_BIASEN ; 
 int WM8350_CODEC_ISEL_MASK ; 
 int /*<<< orphan*/  WM8350_DAC_MUTE ; 
 int WM8350_DAC_MUTE_ENA ; 
 int /*<<< orphan*/  WM8350_LOUT1_VOLUME ; 
 int /*<<< orphan*/  WM8350_LOUT2_VOLUME ; 
 int WM8350_OUT1L_ENA ; 
 int WM8350_OUT1R_ENA ; 
 int WM8350_OUT2L_ENA ; 
 int WM8350_OUT2R_ENA ; 
 int WM8350_OUTPUT_DRAIN_EN ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_1 ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_3 ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_4 ; 
 int /*<<< orphan*/  WM8350_ROUT1_VOLUME ; 
 int /*<<< orphan*/  WM8350_ROUT2_VOLUME ; 
 int WM8350_SYSCLK_ENA ; 
 int WM8350_VBUFEN ; 
 int WM8350_VMIDEN ; 
 int WM8350_VMID_300K ; 
 int WM8350_VMID_50K ; 
 int WM8350_VMID_5K ; 
 int WM8350_VMID_MASK ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8350_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8350_data *priv = snd_soc_component_get_drvdata(component);
	struct wm8350 *wm8350 = priv->wm8350;
	struct wm8350_audio_platform_data *platform =
		wm8350->codec.platform_data;
	u16 pm1;
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1) &
		    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
		wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_VMID_50K |
				 platform->codec_current_on << 14);
		break;

	case SND_SOC_BIAS_PREPARE:
		pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1);
		pm1 &= ~WM8350_VMID_MASK;
		wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_VMID_50K);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies),
						    priv->supplies);
			if (ret != 0)
				return ret;

			/* Enable the system clock */
			wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4,
					WM8350_SYSCLK_ENA);

			/* mute DAC & outputs */
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE,
					WM8350_DAC_MUTE_ENA);

			/* discharge cap memory */
			wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL,
					 platform->dis_out1 |
					 (platform->dis_out2 << 2) |
					 (platform->dis_out3 << 4) |
					 (platform->dis_out4 << 6));

			/* wait for discharge */
			schedule_timeout_interruptible(msecs_to_jiffies
						       (platform->
							cap_discharge_msecs));

			/* enable antipop */
			wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL,
					 (platform->vmid_s_curve << 8));

			/* ramp up vmid */
			wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
					 (platform->
					  codec_current_charge << 14) |
					 WM8350_VMID_5K | WM8350_VMIDEN |
					 WM8350_VBUFEN);

			/* wait for vmid */
			schedule_timeout_interruptible(msecs_to_jiffies
						       (platform->
							vmid_charge_msecs));

			/* turn on vmid 300k  */
			pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
			pm1 |= WM8350_VMID_300K |
				(platform->codec_current_standby << 14);
			wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
					 pm1);


			/* enable analogue bias */
			pm1 |= WM8350_BIASEN;
			wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1, pm1);

			/* disable antipop */
			wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL, 0);

		} else {
			/* turn on vmid 300k and reduce current */
			pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
			wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
					 pm1 | WM8350_VMID_300K |
					 (platform->
					  codec_current_standby << 14));

		}
		break;

	case SND_SOC_BIAS_OFF:

		/* mute DAC & enable outputs */
		wm8350_set_bits(wm8350, WM8350_DAC_MUTE, WM8350_DAC_MUTE_ENA);

		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_3,
				WM8350_OUT1L_ENA | WM8350_OUT1R_ENA |
				WM8350_OUT2L_ENA | WM8350_OUT2R_ENA);

		/* enable anti pop S curve */
		wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL,
				 (platform->vmid_s_curve << 8));

		/* turn off vmid  */
		pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1) &
		    ~WM8350_VMIDEN;
		wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1, pm1);

		/* wait */
		schedule_timeout_interruptible(msecs_to_jiffies
					       (platform->
						vmid_discharge_msecs));

		wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL,
				 (platform->vmid_s_curve << 8) |
				 platform->dis_out1 |
				 (platform->dis_out2 << 2) |
				 (platform->dis_out3 << 4) |
				 (platform->dis_out4 << 6));

		/* turn off VBuf and drain */
		pm1 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_1) &
		    ~(WM8350_VBUFEN | WM8350_VMID_MASK);
		wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_OUTPUT_DRAIN_EN);

		/* wait */
		schedule_timeout_interruptible(msecs_to_jiffies
					       (platform->drain_msecs));

		pm1 &= ~WM8350_BIASEN;
		wm8350_reg_write(wm8350, WM8350_POWER_MGMT_1, pm1);

		/* disable anti-pop */
		wm8350_reg_write(wm8350, WM8350_ANTI_POP_CONTROL, 0);

		wm8350_clear_bits(wm8350, WM8350_LOUT1_VOLUME,
				  WM8350_OUT1L_ENA);
		wm8350_clear_bits(wm8350, WM8350_ROUT1_VOLUME,
				  WM8350_OUT1R_ENA);
		wm8350_clear_bits(wm8350, WM8350_LOUT2_VOLUME,
				  WM8350_OUT2L_ENA);
		wm8350_clear_bits(wm8350, WM8350_ROUT2_VOLUME,
				  WM8350_OUT2R_ENA);

		/* disable clock gen */
		wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4,
				  WM8350_SYSCLK_ENA);

		regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				       priv->supplies);
		break;
	}
	return 0;
}