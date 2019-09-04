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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct phy {TYPE_1__ dev; } ;
struct of_phandle_args {scalar_t__ np; } ;
struct device {int dummy; } ;
struct class_dev_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_dev_iter_exit (struct class_dev_iter*) ; 
 int /*<<< orphan*/  class_dev_iter_init (struct class_dev_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* class_dev_iter_next (struct class_dev_iter*) ; 
 int /*<<< orphan*/  phy_class ; 
 struct phy* to_phy (struct device*) ; 

struct phy *of_phy_simple_xlate(struct device *dev, struct of_phandle_args
	*args)
{
	struct phy *phy;
	struct class_dev_iter iter;

	class_dev_iter_init(&iter, phy_class, NULL, NULL);
	while ((dev = class_dev_iter_next(&iter))) {
		phy = to_phy(dev);
		if (args->np != phy->dev.of_node)
			continue;

		class_dev_iter_exit(&iter);
		return phy;
	}

	class_dev_iter_exit(&iter);
	return ERR_PTR(-ENODEV);
}