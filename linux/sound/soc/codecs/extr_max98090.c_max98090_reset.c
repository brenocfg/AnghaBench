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
struct max98090_priv {TYPE_1__* component; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98090_REG_SOFTWARE_RESET ; 
 int /*<<< orphan*/  M98090_SWRESET_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98090_reset(struct max98090_priv *max98090)
{
	int ret;

	/* Reset the codec by writing to this write-only reset register */
	ret = regmap_write(max98090->regmap, M98090_REG_SOFTWARE_RESET,
		M98090_SWRESET_MASK);
	if (ret < 0) {
		dev_err(max98090->component->dev,
			"Failed to reset codec: %d\n", ret);
		return ret;
	}

	msleep(20);
	return ret;
}