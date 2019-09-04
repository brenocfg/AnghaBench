#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wm8955_priv {TYPE_1__* supplies; } ;
struct wm8955_pdata {scalar_t__ monoin_diff; scalar_t__ out2_speaker; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM8955_ADDITIONAL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8955_BASS_CONTROL ; 
 int WM8955_BB ; 
 int WM8955_DMEN ; 
 int WM8955_LDVU ; 
 int /*<<< orphan*/  WM8955_LEFT_DAC_VOLUME ; 
 int WM8955_LO1VU ; 
 int WM8955_LO1ZC ; 
 int WM8955_LO2VU ; 
 int WM8955_LO2ZC ; 
 int /*<<< orphan*/  WM8955_LOUT1_VOLUME ; 
 int /*<<< orphan*/  WM8955_LOUT2_VOLUME ; 
 int /*<<< orphan*/  WM8955_MONOOUT_VOLUME ; 
 int /*<<< orphan*/  WM8955_MONO_OUT_MIX_1 ; 
 int WM8955_MOZC ; 
 int WM8955_RDVU ; 
 int /*<<< orphan*/  WM8955_RIGHT_DAC_VOLUME ; 
 int WM8955_RO1VU ; 
 int WM8955_RO1ZC ; 
 int WM8955_RO2VU ; 
 int WM8955_RO2ZC ; 
 int /*<<< orphan*/  WM8955_ROUT1_VOLUME ; 
 int WM8955_ROUT2INV ; 
 int /*<<< orphan*/  WM8955_ROUT2_VOLUME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8955_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm8955_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8955_reset (struct snd_soc_component*) ; 
 int /*<<< orphan*/ * wm8955_supply_names ; 

__attribute__((used)) static int wm8955_probe(struct snd_soc_component *component)
{
	struct wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	struct wm8955_pdata *pdata = dev_get_platdata(component->dev);
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(wm8955->supplies); i++)
		wm8955->supplies[i].supply = wm8955_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev, ARRAY_SIZE(wm8955->supplies),
				 wm8955->supplies);
	if (ret != 0) {
		dev_err(component->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8955->supplies),
				    wm8955->supplies);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = wm8955_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		goto err_enable;
	}

	/* Change some default settings - latch VU and enable ZC */
	snd_soc_component_update_bits(component, WM8955_LEFT_DAC_VOLUME,
			    WM8955_LDVU, WM8955_LDVU);
	snd_soc_component_update_bits(component, WM8955_RIGHT_DAC_VOLUME,
			    WM8955_RDVU, WM8955_RDVU);
	snd_soc_component_update_bits(component, WM8955_LOUT1_VOLUME,
			    WM8955_LO1VU | WM8955_LO1ZC,
			    WM8955_LO1VU | WM8955_LO1ZC);
	snd_soc_component_update_bits(component, WM8955_ROUT1_VOLUME,
			    WM8955_RO1VU | WM8955_RO1ZC,
			    WM8955_RO1VU | WM8955_RO1ZC);
	snd_soc_component_update_bits(component, WM8955_LOUT2_VOLUME,
			    WM8955_LO2VU | WM8955_LO2ZC,
			    WM8955_LO2VU | WM8955_LO2ZC);
	snd_soc_component_update_bits(component, WM8955_ROUT2_VOLUME,
			    WM8955_RO2VU | WM8955_RO2ZC,
			    WM8955_RO2VU | WM8955_RO2ZC);
	snd_soc_component_update_bits(component, WM8955_MONOOUT_VOLUME,
			    WM8955_MOZC, WM8955_MOZC);

	/* Also enable adaptive bass boost by default */
	snd_soc_component_update_bits(component, WM8955_BASS_CONTROL, WM8955_BB, WM8955_BB);

	/* Set platform data values */
	if (pdata) {
		if (pdata->out2_speaker)
			snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_2,
					    WM8955_ROUT2INV, WM8955_ROUT2INV);

		if (pdata->monoin_diff)
			snd_soc_component_update_bits(component, WM8955_MONO_OUT_MIX_1,
					    WM8955_DMEN, WM8955_DMEN);
	}

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Bias level configuration will have done an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies), wm8955->supplies);

	return 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies), wm8955->supplies);
	return ret;
}