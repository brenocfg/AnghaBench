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
struct snd_soc_dai_link {int /*<<< orphan*/  stream_name; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int num_links; TYPE_2__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  attr_group ; 
 int /*<<< orphan*/  kernel_kobj ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pisnd_card ; 
 struct snd_soc_dai_link* pisnd_dai ; 
 int /*<<< orphan*/  pisnd_init_gpio (TYPE_2__*) ; 
 int /*<<< orphan*/  pisnd_kobj ; 
 int /*<<< orphan*/  pisnd_spi_get_id () ; 
 int /*<<< orphan*/  pisnd_spi_get_serial () ; 
 int /*<<< orphan*/  pisnd_spi_get_version () ; 
 int pisnd_spi_init (TYPE_2__*) ; 
 int /*<<< orphan*/  pisnd_spi_uninit () ; 
 int /*<<< orphan*/  pisnd_uninit_gpio () ; 
 int /*<<< orphan*/  printe (char*,int) ; 
 int /*<<< orphan*/  printi (char*,...) ; 
 int snd_soc_register_card (TYPE_1__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pisnd_probe(struct platform_device *pdev)
{
	int ret = 0;
	int i;

	ret = pisnd_spi_init(&pdev->dev);
	if (ret < 0) {
		printe("pisnd_spi_init failed: %d\n", ret);
		return ret;
	}

	printi("Detected Pisound card:\n");
	printi("\tSerial:  %s\n", pisnd_spi_get_serial());
	printi("\tVersion: %s\n", pisnd_spi_get_version());
	printi("\tId:      %s\n", pisnd_spi_get_id());

	pisnd_kobj = kobject_create_and_add("pisound", kernel_kobj);
	if (!pisnd_kobj) {
		pisnd_spi_uninit();
		return -ENOMEM;
	}

	ret = sysfs_create_group(pisnd_kobj, &attr_group);
	if (ret < 0) {
		pisnd_spi_uninit();
		kobject_put(pisnd_kobj);
		return -ENOMEM;
	}

	pisnd_init_gpio(&pdev->dev);
	pisnd_card.dev = &pdev->dev;

	if (pdev->dev.of_node) {
		struct device_node *i2s_node;

		i2s_node = of_parse_phandle(
			pdev->dev.of_node,
			"i2s-controller",
			0
			);

		for (i = 0; i < pisnd_card.num_links; ++i) {
			struct snd_soc_dai_link *dai = &pisnd_dai[i];

			if (i2s_node) {
				dai->cpu_dai_name = NULL;
				dai->cpu_of_node = i2s_node;
				dai->platform_name = NULL;
				dai->platform_of_node = i2s_node;
				dai->stream_name = pisnd_spi_get_serial();
			}
		}
	}

	ret = snd_soc_register_card(&pisnd_card);

	if (ret < 0) {
		if (ret != -EPROBE_DEFER)
			printe("snd_soc_register_card() failed: %d\n", ret);
		pisnd_uninit_gpio();
		kobject_put(pisnd_kobj);
		pisnd_spi_uninit();
	}

	return ret;
}