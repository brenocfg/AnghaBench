#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sti_uniperiph_data {void* dai; struct platform_device* pdev; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct sti_uniperiph_data*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  dmaengine_pcm_config ; 
 int sti_uniperiph_cpu_dai_of (struct device_node*,struct sti_uniperiph_data*) ; 
 int /*<<< orphan*/  sti_uniperiph_dai_component ; 

__attribute__((used)) static int sti_uniperiph_probe(struct platform_device *pdev)
{
	struct sti_uniperiph_data *priv;
	struct device_node *node = pdev->dev.of_node;
	int ret;

	/* Allocate the private data and the CPU_DAI array */
	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->dai = devm_kzalloc(&pdev->dev, sizeof(*priv->dai), GFP_KERNEL);
	if (!priv->dai)
		return -ENOMEM;

	priv->pdev = pdev;

	ret = sti_uniperiph_cpu_dai_of(node, priv);

	dev_set_drvdata(&pdev->dev, priv);

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &sti_uniperiph_dai_component,
					      priv->dai, 1);
	if (ret < 0)
		return ret;

	return devm_snd_dmaengine_pcm_register(&pdev->dev,
					       &dmaengine_pcm_config, 0);
}