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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_ac97 {int dummy; } ;
typedef  struct snd_ac97 regmap ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 int /*<<< orphan*/  AC97_MASTER ; 
 int /*<<< orphan*/  AC97_PCM ; 
 int /*<<< orphan*/  AC97_REC_GAIN ; 
 int /*<<< orphan*/  AC97_SURROUND_MASTER ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 scalar_t__ IS_ERR (struct snd_ac97*) ; 
 int PTR_ERR (struct snd_ac97*) ; 
 int /*<<< orphan*/  ad1980_regmap_config ; 
 int ad1980_reset (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct snd_ac97* regmap_init_ac97 (struct snd_ac97*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_component_exit_regmap (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,struct snd_ac97*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_free_ac97_component (struct snd_ac97*) ; 
 struct snd_ac97* snd_soc_new_ac97_component (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad1980_soc_probe(struct snd_soc_component *component)
{
	struct snd_ac97 *ac97;
	struct regmap *regmap;
	int ret;
	u16 vendor_id2;
	u16 ext_status;

	ac97 = snd_soc_new_ac97_component(component, 0, 0);
	if (IS_ERR(ac97)) {
		ret = PTR_ERR(ac97);
		dev_err(component->dev, "Failed to register AC97 component: %d\n", ret);
		return ret;
	}

	regmap = regmap_init_ac97(ac97, &ad1980_regmap_config);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		goto err_free_ac97;
	}

	snd_soc_component_init_regmap(component, regmap);
	snd_soc_component_set_drvdata(component, ac97);

	ret = ad1980_reset(component, 0);
	if (ret < 0)
		goto reset_err;

	vendor_id2 = snd_soc_component_read32(component, AC97_VENDOR_ID2);
	if (vendor_id2 == 0x5374) {
		dev_warn(component->dev,
			"Found AD1981 - only 2/2 IN/OUT Channels supported\n");
	}

	/* unmute captures and playbacks volume */
	snd_soc_component_write(component, AC97_MASTER, 0x0000);
	snd_soc_component_write(component, AC97_PCM, 0x0000);
	snd_soc_component_write(component, AC97_REC_GAIN, 0x0000);
	snd_soc_component_write(component, AC97_CENTER_LFE_MASTER, 0x0000);
	snd_soc_component_write(component, AC97_SURROUND_MASTER, 0x0000);

	/*power on LFE/CENTER/Surround DACs*/
	ext_status = snd_soc_component_read32(component, AC97_EXTENDED_STATUS);
	snd_soc_component_write(component, AC97_EXTENDED_STATUS, ext_status&~0x3800);

	return 0;

reset_err:
	snd_soc_component_exit_regmap(component);
err_free_ac97:
	snd_soc_free_ac97_component(ac97);
	return ret;
}