#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* platform_of_node; struct device_node* cpu_of_node; int /*<<< orphan*/ * ops; scalar_t__ init; } ;
struct snd_rpi_simple_drvdata {int /*<<< orphan*/  card_name; struct snd_soc_dai_link* dai; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct snd_soc_dai_link* dai_link; int /*<<< orphan*/  name; TYPE_3__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int devm_snd_soc_register_card (TYPE_3__*,TYPE_1__*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ snd_rpi_simple ; 
 scalar_t__ snd_rpi_simple_init ; 
 int /*<<< orphan*/  snd_rpi_simple_of_match ; 
 int /*<<< orphan*/  snd_rpi_simple_ops ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct snd_rpi_simple_drvdata*) ; 

__attribute__((used)) static int snd_rpi_simple_probe(struct platform_device *pdev)
{
	int ret = 0;
	const struct of_device_id *of_id;

	snd_rpi_simple.dev = &pdev->dev;
	of_id = of_match_node(snd_rpi_simple_of_match, pdev->dev.of_node);

	if (pdev->dev.of_node && of_id->data) {
		struct device_node *i2s_node;
		struct snd_rpi_simple_drvdata *drvdata =
			(struct snd_rpi_simple_drvdata *) of_id->data;
		struct snd_soc_dai_link *dai = drvdata->dai;

		snd_soc_card_set_drvdata(&snd_rpi_simple, drvdata);

		/* More complex drivers might override individual functions */
		if (!dai->init)
			dai->init = snd_rpi_simple_init;
		if (!dai->ops)
			dai->ops = &snd_rpi_simple_ops;

		snd_rpi_simple.name = drvdata->card_name;

		snd_rpi_simple.dai_link = dai;
		i2s_node = of_parse_phandle(pdev->dev.of_node,
				"i2s-controller", 0);
		if (!i2s_node) {
			pr_err("Failed to find i2s-controller DT node\n");
			return -ENODEV;
		}

		dai->cpu_of_node = i2s_node;
		dai->platform_of_node = i2s_node;
	}

	ret = devm_snd_soc_register_card(&pdev->dev, &snd_rpi_simple);
	if (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "Failed to register card %d\n", ret);

	return ret;
}