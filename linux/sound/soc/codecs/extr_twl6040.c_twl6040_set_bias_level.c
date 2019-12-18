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
struct twl6040_data {int codec_powered; } ;
struct twl6040 {int dummy; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  TWL6040_REG_GPOCTL ; 
 int /*<<< orphan*/  TWL6040_SYSCLK_SEL_LPPLL ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 int twl6040_power (struct twl6040*,int) ; 
 int twl6040_set_pll (struct twl6040*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  twl6040_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl6040_set_bias_level(struct snd_soc_component *component,
				enum snd_soc_bias_level level)
{
	struct twl6040 *twl6040 = to_twl6040(component);
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	int ret = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (priv->codec_powered) {
			/* Select low power PLL in standby */
			ret = twl6040_set_pll(twl6040, TWL6040_SYSCLK_SEL_LPPLL,
					      32768, 19200000);
			break;
		}

		ret = twl6040_power(twl6040, 1);
		if (ret)
			break;

		priv->codec_powered = 1;

		/* Set external boost GPO */
		twl6040_write(component, TWL6040_REG_GPOCTL, 0x02);
		break;
	case SND_SOC_BIAS_OFF:
		if (!priv->codec_powered)
			break;

		twl6040_power(twl6040, 0);
		priv->codec_powered = 0;
		break;
	}

	return ret;
}