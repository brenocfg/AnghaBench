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
struct soc_mixer_control {int /*<<< orphan*/  platform_max; int /*<<< orphan*/  max; } ;
struct device {int dummy; } ;
struct cros_ec_codec_data {int /*<<< orphan*/  max_dmic_gain; } ;
struct TYPE_2__ {scalar_t__ private_value; } ;

/* Variables and functions */
 struct cros_ec_codec_data* dev_get_drvdata (struct device*) ; 
 int device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ mic_gain_control ; 

__attribute__((used)) static int cros_ec_set_gain_range(struct device *dev)
{
	struct soc_mixer_control *control;
	struct cros_ec_codec_data *codec_data = dev_get_drvdata(dev);
	int rc;

	rc = device_property_read_u32(dev, "max-dmic-gain",
				      &codec_data->max_dmic_gain);
	if (rc)
		return rc;

	control = (struct soc_mixer_control *)
				mic_gain_control.private_value;
	control->max = codec_data->max_dmic_gain;
	control->platform_max = codec_data->max_dmic_gain;

	return 0;
}