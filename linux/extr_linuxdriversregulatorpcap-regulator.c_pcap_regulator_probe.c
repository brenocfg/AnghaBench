#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {void* driver_data; int /*<<< orphan*/  init_data; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {size_t id; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_1__*) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/ * pcap_regulators ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 

__attribute__((used)) static int pcap_regulator_probe(struct platform_device *pdev)
{
	struct regulator_dev *rdev;
	void *pcap = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = { };

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = pcap;

	rdev = devm_regulator_register(&pdev->dev, &pcap_regulators[pdev->id],
				       &config);
	if (IS_ERR(rdev))
		return PTR_ERR(rdev);

	platform_set_drvdata(pdev, rdev);

	return 0;
}