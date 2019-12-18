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
struct device {int dummy; } ;
struct cs42l51_private {int /*<<< orphan*/  supplies; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct cs42l51_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cs42l51_remove(struct device *dev)
{
	struct cs42l51_private *cs42l51 = dev_get_drvdata(dev);

	gpiod_set_value_cansleep(cs42l51->reset_gpio, 1);

	return regulator_bulk_disable(ARRAY_SIZE(cs42l51->supplies),
				      cs42l51->supplies);
}