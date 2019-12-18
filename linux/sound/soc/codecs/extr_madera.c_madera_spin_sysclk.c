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
struct madera_priv {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void madera_spin_sysclk(struct madera_priv *priv)
{
	struct madera *madera = priv->madera;
	unsigned int val;
	int ret, i;

	/* Skip this if the chip is down */
	if (pm_runtime_suspended(madera->dev))
		return;

	/*
	 * Just read a register a few times to ensure the internal
	 * oscillator sends out a few clocks.
	 */
	for (i = 0; i < 4; i++) {
		ret = regmap_read(madera->regmap, MADERA_SOFTWARE_RESET, &val);
		if (ret)
			dev_err(madera->dev,
				"Failed to read sysclk spin %d: %d\n", i, ret);
	}

	udelay(300);
}