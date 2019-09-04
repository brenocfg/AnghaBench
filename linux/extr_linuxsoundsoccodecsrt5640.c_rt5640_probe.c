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
typedef  int u32 ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5640_priv {int jd_src; int jd_inverted; int ovcd_sf; void* ovcd_th; struct snd_soc_component* component; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5640_DSP_PATH2 ; 
 int /*<<< orphan*/  RT5640_DUMMY1 ; 
#define  RT5640_ID_5639 130 
#define  RT5640_ID_5640 129 
#define  RT5640_ID_5642 128 
 int RT5640_ID_MASK ; 
 int /*<<< orphan*/  RT5640_IN1_IN2 ; 
 int /*<<< orphan*/  RT5640_IN3_IN4 ; 
 int RT5640_IN_DF1 ; 
 int RT5640_IN_DF2 ; 
 int RT5640_JD_SFT ; 
 int RT5640_JD_SRC_GPIO4 ; 
 void* RT5640_MIC1_OVTH_1500UA ; 
 void* RT5640_MIC1_OVTH_2000UA ; 
 void* RT5640_MIC1_OVTH_600UA ; 
 int /*<<< orphan*/  RT5640_MICBIAS ; 
 int RT5640_MIC_OVCD_SF_0P75 ; 
 int RT5640_MIC_OVCD_SF_SFT ; 
 int RT5640_OVCD_SF_1P5 ; 
 int /*<<< orphan*/  RT5640_RESET ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rt5639_specific_dapm_routes ; 
 int /*<<< orphan*/  rt5639_specific_dapm_widgets ; 
 int /*<<< orphan*/  rt5640_dmic_enable (struct snd_soc_component*,int,int) ; 
 int /*<<< orphan*/  rt5640_specific_dapm_routes ; 
 int /*<<< orphan*/  rt5640_specific_dapm_widgets ; 
 int /*<<< orphan*/  rt5640_specific_snd_controls ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5640_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	u32 dmic1_data_pin = 0;
	u32 dmic2_data_pin = 0;
	bool dmic_en = false;
	u32 val;

	/* Check if MCLK provided */
	rt5640->mclk = devm_clk_get(component->dev, "mclk");
	if (PTR_ERR(rt5640->mclk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	rt5640->component = component;

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_OFF);

	snd_soc_component_update_bits(component, RT5640_DUMMY1, 0x0301, 0x0301);
	snd_soc_component_update_bits(component, RT5640_MICBIAS, 0x0030, 0x0030);
	snd_soc_component_update_bits(component, RT5640_DSP_PATH2, 0xfc00, 0x0c00);

	switch (snd_soc_component_read32(component, RT5640_RESET) & RT5640_ID_MASK) {
	case RT5640_ID_5640:
	case RT5640_ID_5642:
		snd_soc_add_component_controls(component,
			rt5640_specific_snd_controls,
			ARRAY_SIZE(rt5640_specific_snd_controls));
		snd_soc_dapm_new_controls(dapm,
			rt5640_specific_dapm_widgets,
			ARRAY_SIZE(rt5640_specific_dapm_widgets));
		snd_soc_dapm_add_routes(dapm,
			rt5640_specific_dapm_routes,
			ARRAY_SIZE(rt5640_specific_dapm_routes));
		break;
	case RT5640_ID_5639:
		snd_soc_dapm_new_controls(dapm,
			rt5639_specific_dapm_widgets,
			ARRAY_SIZE(rt5639_specific_dapm_widgets));
		snd_soc_dapm_add_routes(dapm,
			rt5639_specific_dapm_routes,
			ARRAY_SIZE(rt5639_specific_dapm_routes));
		break;
	default:
		dev_err(component->dev,
			"The driver is for RT5639 RT5640 or RT5642 only\n");
		return -ENODEV;
	}

	/*
	 * Note on some platforms the platform code may need to add device-props
	 * rather then relying only on properties set by the firmware.
	 * Therefor the property parsing MUST be done here, rather then from
	 * rt5640_i2c_probe(), so that the platform-code can attach extra
	 * properties before calling snd_soc_register_card().
	 */
	if (device_property_read_bool(component->dev, "realtek,in1-differential"))
		snd_soc_component_update_bits(component, RT5640_IN1_IN2,
					      RT5640_IN_DF1, RT5640_IN_DF1);

	if (device_property_read_bool(component->dev, "realtek,in2-differential"))
		snd_soc_component_update_bits(component, RT5640_IN3_IN4,
					      RT5640_IN_DF2, RT5640_IN_DF2);

	if (device_property_read_bool(component->dev, "realtek,in3-differential"))
		snd_soc_component_update_bits(component, RT5640_IN1_IN2,
					      RT5640_IN_DF2, RT5640_IN_DF2);

	if (device_property_read_u32(component->dev, "realtek,dmic1-data-pin",
				     &val) == 0 && val) {
		dmic1_data_pin = val - 1;
		dmic_en = true;
	}

	if (device_property_read_u32(component->dev, "realtek,dmic2-data-pin",
				     &val) == 0 && val) {
		dmic2_data_pin = val - 1;
		dmic_en = true;
	}

	if (dmic_en)
		rt5640_dmic_enable(component, dmic1_data_pin, dmic2_data_pin);

	if (device_property_read_u32(component->dev,
				     "realtek,jack-detect-source", &val) == 0) {
		if (val <= RT5640_JD_SRC_GPIO4)
			rt5640->jd_src = val << RT5640_JD_SFT;
		else
			dev_warn(component->dev, "Warning: Invalid jack-detect-source value: %d, leaving jack-detect disabled\n",
				 val);
	}

	if (!device_property_read_bool(component->dev, "realtek,jack-detect-not-inverted"))
		rt5640->jd_inverted = true;

	/*
	 * Testing on various boards has shown that good defaults for the OVCD
	 * threshold and scale-factor are 2000µA and 0.75. For an effective
	 * limit of 1500µA, this seems to be more reliable then 1500µA and 1.0.
	 */
	rt5640->ovcd_th = RT5640_MIC1_OVTH_2000UA;
	rt5640->ovcd_sf = RT5640_MIC_OVCD_SF_0P75;

	if (device_property_read_u32(component->dev,
			"realtek,over-current-threshold-microamp", &val) == 0) {
		switch (val) {
		case 600:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_600UA;
			break;
		case 1500:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_1500UA;
			break;
		case 2000:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_2000UA;
			break;
		default:
			dev_warn(component->dev, "Warning: Invalid over-current-threshold-microamp value: %d, defaulting to 2000uA\n",
				 val);
		}
	}

	if (device_property_read_u32(component->dev,
			"realtek,over-current-scale-factor", &val) == 0) {
		if (val <= RT5640_OVCD_SF_1P5)
			rt5640->ovcd_sf = val << RT5640_MIC_OVCD_SF_SFT;
		else
			dev_warn(component->dev, "Warning: Invalid over-current-scale-factor value: %d, defaulting to 0.75\n",
				 val);
	}

	return 0;
}