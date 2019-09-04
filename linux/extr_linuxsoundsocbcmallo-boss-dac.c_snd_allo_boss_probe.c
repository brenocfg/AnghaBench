#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_bias_level; TYPE_4__* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int digital_gain_0db_limit ; 
 scalar_t__ mute_gpio ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 scalar_t__ slave ; 
 TYPE_1__ snd_allo_boss ; 
 struct snd_soc_dai_link* snd_allo_boss_dai ; 
 int /*<<< orphan*/  snd_allo_boss_gpio_mute (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_allo_boss_set_bias_level ; 
 int snd_soc_register_card (TYPE_1__*) ; 

__attribute__((used)) static int snd_allo_boss_probe(struct platform_device *pdev)
{
	int ret = 0;

	snd_allo_boss.dev = &pdev->dev;

	if (pdev->dev.of_node) {
		struct device_node *i2s_node;
		struct snd_soc_dai_link *dai;

		dai = &snd_allo_boss_dai[0];
		i2s_node = of_parse_phandle(pdev->dev.of_node,
					    "i2s-controller", 0);

		if (i2s_node) {
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = i2s_node;
			dai->platform_name = NULL;
			dai->platform_of_node = i2s_node;
		}

		digital_gain_0db_limit = !of_property_read_bool(
			pdev->dev.of_node, "allo,24db_digital_gain");
		slave = of_property_read_bool(pdev->dev.of_node,
						"allo,slave");

		mute_gpio = devm_gpiod_get_optional(&pdev->dev, "mute",
							GPIOD_OUT_LOW);
		if (IS_ERR(mute_gpio)) {
			ret = PTR_ERR(mute_gpio);
			dev_err(&pdev->dev,
				"failed to get mute gpio: %d\n", ret);
			return ret;
		}

		if (mute_gpio)
			snd_allo_boss.set_bias_level =
				snd_allo_boss_set_bias_level;

		ret = snd_soc_register_card(&snd_allo_boss);
		if (ret) {
			dev_err(&pdev->dev,
				"snd_soc_register_card() failed: %d\n", ret);
			return ret;
		}

		if (mute_gpio)
			snd_allo_boss_gpio_mute(&snd_allo_boss);

		return 0;
	}

	return -EINVAL;
}