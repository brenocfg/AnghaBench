#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {TYPE_2__* dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int devm_snd_soc_register_card (TYPE_2__*,TYPE_1__*) ; 
 int digital_gain_0db_limit ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 scalar_t__ slave ; 
 TYPE_1__ snd_rpi_hifiberry_dacplus ; 
 struct snd_soc_dai_link* snd_rpi_hifiberry_dacplus_dai ; 

__attribute__((used)) static int snd_rpi_hifiberry_dacplus_probe(struct platform_device *pdev)
{
	int ret = 0;

	snd_rpi_hifiberry_dacplus.dev = &pdev->dev;
	if (pdev->dev.of_node) {
		struct device_node *i2s_node;
		struct snd_soc_dai_link *dai;

		dai = &snd_rpi_hifiberry_dacplus_dai[0];
		i2s_node = of_parse_phandle(pdev->dev.of_node,
			"i2s-controller", 0);

		if (i2s_node) {
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = i2s_node;
			dai->platform_name = NULL;
			dai->platform_of_node = i2s_node;
		}

		digital_gain_0db_limit = !of_property_read_bool(
			pdev->dev.of_node, "hifiberry,24db_digital_gain");
		slave = of_property_read_bool(pdev->dev.of_node,
						"hifiberry-dacplus,slave");
	}

	ret = devm_snd_soc_register_card(&pdev->dev,
			&snd_rpi_hifiberry_dacplus);
	if (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);

	return ret;
}