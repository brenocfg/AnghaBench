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
struct pm8916_wcd_analog_priv {int hphl_jack_type_normally_open; int gnd_jack_type_normally_open; int mbhc_btn_enabled; int /*<<< orphan*/ * vref_btn_micb; int /*<<< orphan*/ * vref_btn_cs; int /*<<< orphan*/  micbias_mv; void* micbias2_cap_mode; void* micbias1_cap_mode; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBHC_MAX_BUTTONS ; 
 void* MICB_1_EN_EXT_BYP_CAP ; 
 void* MICB_1_EN_NO_EXT_BYP_CAP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm8916_wcd_analog_parse_dt(struct device *dev,
				       struct pm8916_wcd_analog_priv *priv)
{
	int rval;

	if (of_property_read_bool(dev->of_node, "qcom,micbias1-ext-cap"))
		priv->micbias1_cap_mode = MICB_1_EN_EXT_BYP_CAP;
	else
		priv->micbias1_cap_mode = MICB_1_EN_NO_EXT_BYP_CAP;

	if (of_property_read_bool(dev->of_node, "qcom,micbias2-ext-cap"))
		priv->micbias2_cap_mode = MICB_1_EN_EXT_BYP_CAP;
	else
		priv->micbias2_cap_mode = MICB_1_EN_NO_EXT_BYP_CAP;

	of_property_read_u32(dev->of_node, "qcom,micbias-lvl",
			     &priv->micbias_mv);

	if (of_property_read_bool(dev->of_node,
				  "qcom,hphl-jack-type-normally-open"))
		priv->hphl_jack_type_normally_open = true;
	else
		priv->hphl_jack_type_normally_open = false;

	if (of_property_read_bool(dev->of_node,
				  "qcom,gnd-jack-type-normally-open"))
		priv->gnd_jack_type_normally_open = true;
	else
		priv->gnd_jack_type_normally_open = false;

	priv->mbhc_btn_enabled = true;
	rval = of_property_read_u32_array(dev->of_node,
					  "qcom,mbhc-vthreshold-low",
					  &priv->vref_btn_cs[0],
					  MBHC_MAX_BUTTONS);
	if (rval < 0) {
		priv->mbhc_btn_enabled = false;
	} else {
		rval = of_property_read_u32_array(dev->of_node,
						  "qcom,mbhc-vthreshold-high",
						  &priv->vref_btn_micb[0],
						  MBHC_MAX_BUTTONS);
		if (rval < 0)
			priv->mbhc_btn_enabled = false;
	}

	if (!priv->mbhc_btn_enabled)
		dev_err(dev,
			"DT property missing, MBHC btn detection disabled\n");


	return 0;
}