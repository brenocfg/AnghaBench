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
struct nau8825 {int jkdet_enable; int jkdet_pull_enable; int jkdet_pull_up; int jkdet_polarity; int micbias_voltage; int vref_impedance; int sar_threshold_num; int sar_hysteresis; int sar_voltage; int sar_compare_time; int sar_sampling_time; int key_debounce; int jack_insert_debounce; int jack_eject_debounce; int xtalk_enable; int /*<<< orphan*/ * sar_threshold; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 

__attribute__((used)) static void nau8825_print_device_properties(struct nau8825 *nau8825)
{
	int i;
	struct device *dev = nau8825->dev;

	dev_dbg(dev, "jkdet-enable:         %d\n", nau8825->jkdet_enable);
	dev_dbg(dev, "jkdet-pull-enable:    %d\n", nau8825->jkdet_pull_enable);
	dev_dbg(dev, "jkdet-pull-up:        %d\n", nau8825->jkdet_pull_up);
	dev_dbg(dev, "jkdet-polarity:       %d\n", nau8825->jkdet_polarity);
	dev_dbg(dev, "micbias-voltage:      %d\n", nau8825->micbias_voltage);
	dev_dbg(dev, "vref-impedance:       %d\n", nau8825->vref_impedance);

	dev_dbg(dev, "sar-threshold-num:    %d\n", nau8825->sar_threshold_num);
	for (i = 0; i < nau8825->sar_threshold_num; i++)
		dev_dbg(dev, "sar-threshold[%d]=%d\n", i,
				nau8825->sar_threshold[i]);

	dev_dbg(dev, "sar-hysteresis:       %d\n", nau8825->sar_hysteresis);
	dev_dbg(dev, "sar-voltage:          %d\n", nau8825->sar_voltage);
	dev_dbg(dev, "sar-compare-time:     %d\n", nau8825->sar_compare_time);
	dev_dbg(dev, "sar-sampling-time:    %d\n", nau8825->sar_sampling_time);
	dev_dbg(dev, "short-key-debounce:   %d\n", nau8825->key_debounce);
	dev_dbg(dev, "jack-insert-debounce: %d\n",
			nau8825->jack_insert_debounce);
	dev_dbg(dev, "jack-eject-debounce:  %d\n",
			nau8825->jack_eject_debounce);
	dev_dbg(dev, "crosstalk-enable:     %d\n",
			nau8825->xtalk_enable);
}