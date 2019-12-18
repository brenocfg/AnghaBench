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
struct nau8825 {int jkdet_polarity; int micbias_voltage; int vref_impedance; int sar_threshold_num; int* sar_threshold; int sar_hysteresis; int sar_voltage; int sar_compare_time; int sar_sampling_time; int key_debounce; int jack_insert_debounce; int jack_eject_debounce; int /*<<< orphan*/ * mclk; void* xtalk_enable; void* jkdet_pull_up; void* jkdet_pull_enable; void* jkdet_enable; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* device_property_read_bool (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int device_property_read_u32_array (struct device*,char*,int*,int) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int nau8825_read_device_properties(struct device *dev,
	struct nau8825 *nau8825) {
	int ret;

	nau8825->jkdet_enable = device_property_read_bool(dev,
		"nuvoton,jkdet-enable");
	nau8825->jkdet_pull_enable = device_property_read_bool(dev,
		"nuvoton,jkdet-pull-enable");
	nau8825->jkdet_pull_up = device_property_read_bool(dev,
		"nuvoton,jkdet-pull-up");
	ret = device_property_read_u32(dev, "nuvoton,jkdet-polarity",
		&nau8825->jkdet_polarity);
	if (ret)
		nau8825->jkdet_polarity = 1;
	ret = device_property_read_u32(dev, "nuvoton,micbias-voltage",
		&nau8825->micbias_voltage);
	if (ret)
		nau8825->micbias_voltage = 6;
	ret = device_property_read_u32(dev, "nuvoton,vref-impedance",
		&nau8825->vref_impedance);
	if (ret)
		nau8825->vref_impedance = 2;
	ret = device_property_read_u32(dev, "nuvoton,sar-threshold-num",
		&nau8825->sar_threshold_num);
	if (ret)
		nau8825->sar_threshold_num = 4;
	ret = device_property_read_u32_array(dev, "nuvoton,sar-threshold",
		nau8825->sar_threshold, nau8825->sar_threshold_num);
	if (ret) {
		nau8825->sar_threshold[0] = 0x08;
		nau8825->sar_threshold[1] = 0x12;
		nau8825->sar_threshold[2] = 0x26;
		nau8825->sar_threshold[3] = 0x73;
	}
	ret = device_property_read_u32(dev, "nuvoton,sar-hysteresis",
		&nau8825->sar_hysteresis);
	if (ret)
		nau8825->sar_hysteresis = 0;
	ret = device_property_read_u32(dev, "nuvoton,sar-voltage",
		&nau8825->sar_voltage);
	if (ret)
		nau8825->sar_voltage = 6;
	ret = device_property_read_u32(dev, "nuvoton,sar-compare-time",
		&nau8825->sar_compare_time);
	if (ret)
		nau8825->sar_compare_time = 1;
	ret = device_property_read_u32(dev, "nuvoton,sar-sampling-time",
		&nau8825->sar_sampling_time);
	if (ret)
		nau8825->sar_sampling_time = 1;
	ret = device_property_read_u32(dev, "nuvoton,short-key-debounce",
		&nau8825->key_debounce);
	if (ret)
		nau8825->key_debounce = 3;
	ret = device_property_read_u32(dev, "nuvoton,jack-insert-debounce",
		&nau8825->jack_insert_debounce);
	if (ret)
		nau8825->jack_insert_debounce = 7;
	ret = device_property_read_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8825->jack_eject_debounce);
	if (ret)
		nau8825->jack_eject_debounce = 0;
	nau8825->xtalk_enable = device_property_read_bool(dev,
		"nuvoton,crosstalk-enable");

	nau8825->mclk = devm_clk_get(dev, "mclk");
	if (PTR_ERR(nau8825->mclk) == -EPROBE_DEFER) {
		return -EPROBE_DEFER;
	} else if (PTR_ERR(nau8825->mclk) == -ENOENT) {
		/* The MCLK is managed externally or not used at all */
		nau8825->mclk = NULL;
		dev_info(dev, "No 'mclk' clock found, assume MCLK is managed externally");
	} else if (IS_ERR(nau8825->mclk)) {
		return -EINVAL;
	}

	return 0;
}