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
struct snd_soc_dapm_context {int dummy; } ;
struct TYPE_2__ {scalar_t__ cbj_en; } ;
struct rt286_priv {int /*<<< orphan*/  regmap; TYPE_1__ pdata; int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT286_CBJ_CTRL1 ; 
 int /*<<< orphan*/  RT286_CBJ_CTRL2 ; 
 int /*<<< orphan*/  RT286_DC_GAIN ; 
 int /*<<< orphan*/  RT286_GET_HP_SENSE ; 
 int /*<<< orphan*/  RT286_GET_MIC1_SENSE ; 
 int /*<<< orphan*/  RT286_SET_MIC1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int rt286_jack_detect(struct rt286_priv *rt286, bool *hp, bool *mic)
{
	struct snd_soc_dapm_context *dapm;
	unsigned int val, buf;

	*hp = false;
	*mic = false;

	if (!rt286->component)
		return -EINVAL;

	dapm = snd_soc_component_get_dapm(rt286->component);

	if (rt286->pdata.cbj_en) {
		regmap_read(rt286->regmap, RT286_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		if (*hp) {
			/* power on HV,VERF */
			regmap_update_bits(rt286->regmap,
				RT286_DC_GAIN, 0x200, 0x200);

			snd_soc_dapm_force_enable_pin(dapm, "HV");
			snd_soc_dapm_force_enable_pin(dapm, "VREF");
			/* power LDO1 */
			snd_soc_dapm_force_enable_pin(dapm, "LDO1");
			snd_soc_dapm_sync(dapm);

			regmap_write(rt286->regmap, RT286_SET_MIC1, 0x24);
			msleep(50);

			regmap_update_bits(rt286->regmap,
				RT286_CBJ_CTRL1, 0xfcc0, 0xd400);
			msleep(300);
			regmap_read(rt286->regmap, RT286_CBJ_CTRL2, &val);

			if (0x0070 == (val & 0x0070)) {
				*mic = true;
			} else {
				regmap_update_bits(rt286->regmap,
					RT286_CBJ_CTRL1, 0xfcc0, 0xe400);
				msleep(300);
				regmap_read(rt286->regmap,
					RT286_CBJ_CTRL2, &val);
				if (0x0070 == (val & 0x0070))
					*mic = true;
				else
					*mic = false;
			}
			regmap_update_bits(rt286->regmap,
				RT286_DC_GAIN, 0x200, 0x0);

		} else {
			*mic = false;
			regmap_write(rt286->regmap, RT286_SET_MIC1, 0x20);
			regmap_update_bits(rt286->regmap,
				RT286_CBJ_CTRL1, 0x0400, 0x0000);
		}
	} else {
		regmap_read(rt286->regmap, RT286_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		regmap_read(rt286->regmap, RT286_GET_MIC1_SENSE, &buf);
		*mic = buf & 0x80000000;
	}
	if (!*mic) {
		snd_soc_dapm_disable_pin(dapm, "HV");
		snd_soc_dapm_disable_pin(dapm, "VREF");
	}
	if (!*hp)
		snd_soc_dapm_disable_pin(dapm, "LDO1");
	snd_soc_dapm_sync(dapm);

	return 0;
}