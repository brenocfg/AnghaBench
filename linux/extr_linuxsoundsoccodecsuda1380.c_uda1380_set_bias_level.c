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
struct uda1380_platform_data {int /*<<< orphan*/  gpio_power; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {struct uda1380_platform_data* platform_data; } ;

/* Variables and functions */
 int R02_PON_BIAS ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int UDA1380_CACHEREGNUM ; 
 int UDA1380_MVOL ; 
 int /*<<< orphan*/  UDA1380_PM ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int /*<<< orphan*/  uda1380_cache_dirty ; 
 int uda1380_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda1380_reset (struct snd_soc_component*) ; 
 int /*<<< orphan*/  uda1380_sync_cache (struct snd_soc_component*) ; 
 int /*<<< orphan*/  uda1380_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uda1380_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	int pm = uda1380_read_reg_cache(component, UDA1380_PM);
	int reg;
	struct uda1380_platform_data *pdata = component->dev->platform_data;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		/* ADC, DAC on */
		uda1380_write(component, UDA1380_PM, R02_PON_BIAS | pm);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			if (gpio_is_valid(pdata->gpio_power)) {
				gpio_set_value(pdata->gpio_power, 1);
				mdelay(1);
				uda1380_reset(component);
			}

			uda1380_sync_cache(component);
		}
		uda1380_write(component, UDA1380_PM, 0x0);
		break;
	case SND_SOC_BIAS_OFF:
		if (!gpio_is_valid(pdata->gpio_power))
			break;

		gpio_set_value(pdata->gpio_power, 0);

		/* Mark mixer regs cache dirty to sync them with
		 * codec regs on power on.
		 */
		for (reg = UDA1380_MVOL; reg < UDA1380_CACHEREGNUM; reg++)
			set_bit(reg - 0x10, &uda1380_cache_dirty);
	}
	return 0;
}