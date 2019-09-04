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
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct regulator_dev* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  rdev_dbg (struct regulator_dev*,char*) ; 
 scalar_t__ regulator_fill_coupling_array (struct regulator_dev*) ; 

__attribute__((used)) static int regulator_register_fill_coupling_array(struct device *dev,
						  void *data)
{
	struct regulator_dev *rdev = dev_to_rdev(dev);

	if (!IS_ENABLED(CONFIG_OF))
		return 0;

	if (regulator_fill_coupling_array(rdev))
		rdev_dbg(rdev, "unable to resolve coupling\n");

	return 0;
}