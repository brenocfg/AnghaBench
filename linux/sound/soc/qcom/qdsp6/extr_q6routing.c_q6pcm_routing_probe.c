#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_soc_routing_component ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* routing_data ; 

__attribute__((used)) static int q6pcm_routing_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	routing_data = kzalloc(sizeof(*routing_data), GFP_KERNEL);
	if (!routing_data)
		return -ENOMEM;

	routing_data->dev = dev;

	mutex_init(&routing_data->lock);
	dev_set_drvdata(dev, routing_data);

	return devm_snd_soc_register_component(dev, &msm_soc_routing_component,
					  NULL, 0);
}