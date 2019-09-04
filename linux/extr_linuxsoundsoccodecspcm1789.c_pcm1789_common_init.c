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
struct pcm1789_private {int /*<<< orphan*/  work; int /*<<< orphan*/  reset; struct device* dev; struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pcm1789_private*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct pcm1789_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pcm1789_dai ; 
 int /*<<< orphan*/  pcm1789_work_queue ; 
 int /*<<< orphan*/  soc_component_dev_pcm1789 ; 

int pcm1789_common_init(struct device *dev, struct regmap *regmap)
{
	struct pcm1789_private *pcm1789;

	pcm1789 = devm_kzalloc(dev, sizeof(struct pcm1789_private),
			       GFP_KERNEL);
	if (!pcm1789)
		return -ENOMEM;

	pcm1789->regmap = regmap;
	pcm1789->dev = dev;
	dev_set_drvdata(dev, pcm1789);

	pcm1789->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(pcm1789->reset))
		return PTR_ERR(pcm1789->reset);

	gpiod_set_value_cansleep(pcm1789->reset, 0);
	msleep(300);

	INIT_WORK(&pcm1789->work, pcm1789_work_queue);

	return devm_snd_soc_register_component(dev, &soc_component_dev_pcm1789,
					       &pcm1789_dai, 1);
}