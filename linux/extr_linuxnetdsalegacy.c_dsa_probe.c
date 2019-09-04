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
struct TYPE_5__ {struct dsa_platform_data* platform_data; scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int /*<<< orphan*/ * dsa_ptr; } ;
struct dsa_switch_tree {int dummy; } ;
struct dsa_platform_data {int /*<<< orphan*/ * netdev; struct net_device* of_netdev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct dsa_switch_tree* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct net_device* dsa_dev_to_net_device (int /*<<< orphan*/ *) ; 
 int dsa_of_probe (TYPE_1__*) ; 
 int /*<<< orphan*/  dsa_of_remove (TYPE_1__*) ; 
 int dsa_setup_dst (struct dsa_switch_tree*,struct net_device*,TYPE_1__*,struct dsa_platform_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dsa_switch_tree*) ; 

__attribute__((used)) static int dsa_probe(struct platform_device *pdev)
{
	struct dsa_platform_data *pd = pdev->dev.platform_data;
	struct net_device *dev;
	struct dsa_switch_tree *dst;
	int ret;

	if (pdev->dev.of_node) {
		ret = dsa_of_probe(&pdev->dev);
		if (ret)
			return ret;

		pd = pdev->dev.platform_data;
	}

	if (pd == NULL || (pd->netdev == NULL && pd->of_netdev == NULL))
		return -EINVAL;

	if (pd->of_netdev) {
		dev = pd->of_netdev;
		dev_hold(dev);
	} else {
		dev = dsa_dev_to_net_device(pd->netdev);
	}
	if (dev == NULL) {
		ret = -EPROBE_DEFER;
		goto out;
	}

	if (dev->dsa_ptr != NULL) {
		dev_put(dev);
		ret = -EEXIST;
		goto out;
	}

	dst = devm_kzalloc(&pdev->dev, sizeof(*dst), GFP_KERNEL);
	if (dst == NULL) {
		dev_put(dev);
		ret = -ENOMEM;
		goto out;
	}

	platform_set_drvdata(pdev, dst);

	ret = dsa_setup_dst(dst, dev, &pdev->dev, pd);
	if (ret) {
		dev_put(dev);
		goto out;
	}

	return 0;

out:
	dsa_of_remove(&pdev->dev);

	return ret;
}