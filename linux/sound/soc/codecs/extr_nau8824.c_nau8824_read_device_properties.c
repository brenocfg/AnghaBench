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
struct nau8824 {int jkdet_polarity; int micbias_voltage; int vref_impedance; int sar_threshold_num; int* sar_threshold; int sar_hysteresis; int sar_voltage; int sar_compare_time; int sar_sampling_time; int key_debounce; int jack_eject_debounce; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int device_property_read_u32_array (struct device*,char*,int*,int) ; 

__attribute__((used)) static int nau8824_read_device_properties(struct device *dev,
	struct nau8824 *nau8824) {
	int ret;

	ret = device_property_read_u32(dev, "nuvoton,jkdet-polarity",
		&nau8824->jkdet_polarity);
	if (ret)
		nau8824->jkdet_polarity = 1;
	ret = device_property_read_u32(dev, "nuvoton,micbias-voltage",
		&nau8824->micbias_voltage);
	if (ret)
		nau8824->micbias_voltage = 6;
	ret = device_property_read_u32(dev, "nuvoton,vref-impedance",
		&nau8824->vref_impedance);
	if (ret)
		nau8824->vref_impedance = 2;
	ret = device_property_read_u32(dev, "nuvoton,sar-threshold-num",
		&nau8824->sar_threshold_num);
	if (ret)
		nau8824->sar_threshold_num = 4;
	ret = device_property_read_u32_array(dev, "nuvoton,sar-threshold",
		nau8824->sar_threshold, nau8824->sar_threshold_num);
	if (ret) {
		nau8824->sar_threshold[0] = 0x0a;
		nau8824->sar_threshold[1] = 0x14;
		nau8824->sar_threshold[2] = 0x26;
		nau8824->sar_threshold[3] = 0x73;
	}
	ret = device_property_read_u32(dev, "nuvoton,sar-hysteresis",
		&nau8824->sar_hysteresis);
	if (ret)
		nau8824->sar_hysteresis = 0;
	ret = device_property_read_u32(dev, "nuvoton,sar-voltage",
		&nau8824->sar_voltage);
	if (ret)
		nau8824->sar_voltage = 6;
	ret = device_property_read_u32(dev, "nuvoton,sar-compare-time",
		&nau8824->sar_compare_time);
	if (ret)
		nau8824->sar_compare_time = 1;
	ret = device_property_read_u32(dev, "nuvoton,sar-sampling-time",
		&nau8824->sar_sampling_time);
	if (ret)
		nau8824->sar_sampling_time = 1;
	ret = device_property_read_u32(dev, "nuvoton,short-key-debounce",
		&nau8824->key_debounce);
	if (ret)
		nau8824->key_debounce = 0;
	ret = device_property_read_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8824->jack_eject_debounce);
	if (ret)
		nau8824->jack_eject_debounce = 1;

	return 0;
}