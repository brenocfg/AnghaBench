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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_component {struct device* dev; } ;
struct device {int dummy; } ;
struct da7213_platform_data {int /*<<< orphan*/  dmic_clk_rate; int /*<<< orphan*/  dmic_samplephase; int /*<<< orphan*/  dmic_data_sel; void* micbias2_lvl; void* micbias1_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7213_DMIC_CLK_3_0MHZ ; 
 int /*<<< orphan*/  DA7213_DMIC_DATA_LRISE_RFALL ; 
 int /*<<< orphan*/  DA7213_DMIC_SAMPLE_ON_CLKEDGE ; 
 void* DA7213_MICBIAS_2_2V ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  da7213_of_dmic_clkrate (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da7213_of_dmic_data_sel (struct snd_soc_component*,char const*) ; 
 int /*<<< orphan*/  da7213_of_dmic_samplephase (struct snd_soc_component*,char const*) ; 
 void* da7213_of_micbias_lvl (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_property_read_string (struct device*,char*,char const**) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 struct da7213_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct da7213_platform_data
	*da7213_fw_to_pdata(struct snd_soc_component *component)
{
	struct device *dev = component->dev;
	struct da7213_platform_data *pdata;
	const char *fw_str;
	u32 fw_val32;

	pdata = devm_kzalloc(component->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	if (device_property_read_u32(dev, "dlg,micbias1-lvl", &fw_val32) >= 0)
		pdata->micbias1_lvl = da7213_of_micbias_lvl(component, fw_val32);
	else
		pdata->micbias1_lvl = DA7213_MICBIAS_2_2V;

	if (device_property_read_u32(dev, "dlg,micbias2-lvl", &fw_val32) >= 0)
		pdata->micbias2_lvl = da7213_of_micbias_lvl(component, fw_val32);
	else
		pdata->micbias2_lvl = DA7213_MICBIAS_2_2V;

	if (!device_property_read_string(dev, "dlg,dmic-data-sel", &fw_str))
		pdata->dmic_data_sel = da7213_of_dmic_data_sel(component, fw_str);
	else
		pdata->dmic_data_sel = DA7213_DMIC_DATA_LRISE_RFALL;

	if (!device_property_read_string(dev, "dlg,dmic-samplephase", &fw_str))
		pdata->dmic_samplephase =
			da7213_of_dmic_samplephase(component, fw_str);
	else
		pdata->dmic_samplephase = DA7213_DMIC_SAMPLE_ON_CLKEDGE;

	if (device_property_read_u32(dev, "dlg,dmic-clkrate", &fw_val32) >= 0)
		pdata->dmic_clk_rate = da7213_of_dmic_clkrate(component, fw_val32);
	else
		pdata->dmic_clk_rate = DA7213_DMIC_CLK_3_0MHZ;

	return pdata;
}