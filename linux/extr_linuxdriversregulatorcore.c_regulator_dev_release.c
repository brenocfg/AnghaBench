#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct regulator_dev {TYPE_1__ dev; struct regulator_dev* constraints; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct regulator_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct regulator_dev*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regulator_dev_release(struct device *dev)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);

	kfree(rdev->constraints);
	of_node_put(rdev->dev.of_node);
	kfree(rdev);
}