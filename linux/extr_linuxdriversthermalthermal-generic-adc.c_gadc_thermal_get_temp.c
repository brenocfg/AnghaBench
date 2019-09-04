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
struct gadc_thermal_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gadc_thermal_adc_to_temp (struct gadc_thermal_info*,int) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int gadc_thermal_get_temp(void *data, int *temp)
{
	struct gadc_thermal_info *gti = data;
	int val;
	int ret;

	ret = iio_read_channel_processed(gti->channel, &val);
	if (ret < 0) {
		dev_err(gti->dev, "IIO channel read failed %d\n", ret);
		return ret;
	}
	*temp = gadc_thermal_adc_to_temp(gti, val);

	return 0;
}