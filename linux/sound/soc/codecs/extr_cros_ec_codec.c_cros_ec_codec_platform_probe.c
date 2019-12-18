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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct cros_ec_device {int dummy; } ;
struct cros_ec_codec_data {struct cros_ec_device* ec_device; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cros_ec_component_driver ; 
 int /*<<< orphan*/  cros_ec_dai ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_codec_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cros_ec_codec_data*) ; 

__attribute__((used)) static int cros_ec_codec_platform_probe(struct platform_device *pd)
{
	struct device *dev = &pd->dev;
	struct cros_ec_device *ec_device = dev_get_drvdata(pd->dev.parent);
	struct cros_ec_codec_data *codec_data;

	codec_data = devm_kzalloc(dev, sizeof(struct cros_ec_codec_data),
				  GFP_KERNEL);
	if (!codec_data)
		return -ENOMEM;

	codec_data->dev = dev;
	codec_data->ec_device = ec_device;

	platform_set_drvdata(pd, codec_data);

	return devm_snd_soc_register_component(dev, &cros_ec_component_driver,
					  cros_ec_dai, ARRAY_SIZE(cros_ec_dai));
}