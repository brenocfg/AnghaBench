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
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 struct regulator_dev* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  regulator_class ; 
 int /*<<< orphan*/  regulator_match ; 

__attribute__((used)) static struct regulator_dev *regulator_lookup_by_name(const char *name)
{
	struct device *dev;

	dev = class_find_device(&regulator_class, NULL, name, regulator_match);

	return dev ? dev_to_rdev(dev) : NULL;
}