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
struct regmap {int dummy; } ;
struct pcm179x_private {struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pcm179x_private*) ; 
 struct pcm179x_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcm179x_dai ; 
 int /*<<< orphan*/  soc_component_dev_pcm179x ; 

int pcm179x_common_init(struct device *dev, struct regmap *regmap)
{
	struct pcm179x_private *pcm179x;

	pcm179x = devm_kzalloc(dev, sizeof(struct pcm179x_private),
				GFP_KERNEL);
	if (!pcm179x)
		return -ENOMEM;

	pcm179x->regmap = regmap;
	dev_set_drvdata(dev, pcm179x);

	return devm_snd_soc_register_component(dev,
			&soc_component_dev_pcm179x, &pcm179x_dai, 1);
}