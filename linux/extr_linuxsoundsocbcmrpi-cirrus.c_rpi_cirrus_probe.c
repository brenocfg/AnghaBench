#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rpi_cirrus_priv {int min_rate_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  card_rate; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {struct device_node* platform_of_node; struct device_node* cpu_of_node; } ;
struct TYPE_9__ {TYPE_4__* dev; } ;

/* Variables and functions */
 size_t DAI_WM5102 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPI_CIRRUS_DEFAULT_RATE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct rpi_cirrus_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ rpi_cirrus_card ; 
 TYPE_2__* rpi_cirrus_dai ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct rpi_cirrus_priv*) ; 

__attribute__((used)) static int rpi_cirrus_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct rpi_cirrus_priv *priv;
	struct device_node *i2s_node;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->min_rate_idx = 1; /* min samplerate 32kHz */
	priv->card_rate = RPI_CIRRUS_DEFAULT_RATE;

	mutex_init(&priv->lock);

	snd_soc_card_set_drvdata(&rpi_cirrus_card, priv);

	if (!pdev->dev.of_node)
		return -ENODEV;

	i2s_node = of_parse_phandle(
			pdev->dev.of_node, "i2s-controller", 0);
	if (!i2s_node) {
		dev_err(&pdev->dev, "i2s-controller missing in DT\n");
		return -ENODEV;
	}

	rpi_cirrus_dai[DAI_WM5102].cpu_of_node = i2s_node;
	rpi_cirrus_dai[DAI_WM5102].platform_of_node = i2s_node;

	rpi_cirrus_card.dev = &pdev->dev;

	ret = devm_snd_soc_register_card(&pdev->dev, &rpi_cirrus_card);
	if (ret) {
		if (ret == -EPROBE_DEFER)
			dev_dbg(&pdev->dev,
				"register card requested probe deferral\n");
		else
			dev_err(&pdev->dev,
				"Failed to register card: %d\n", ret);
	}

	return ret;
}