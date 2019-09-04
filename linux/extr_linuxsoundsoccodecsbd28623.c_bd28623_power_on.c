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
struct bd28623_priv {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bd28623_power_on(struct bd28623_priv *bd)
{
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(bd->supplies), bd->supplies);
	if (ret) {
		dev_err(bd->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	gpiod_set_value_cansleep(bd->reset_gpio, 0);
	usleep_range(300000, 400000);

	return 0;
}