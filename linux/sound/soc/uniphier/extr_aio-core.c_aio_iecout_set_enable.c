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
struct uniphier_aio_chip {struct regmap* regmap_sg; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_AOUTEN ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aio_iecout_set_enable(struct uniphier_aio_chip *chip, bool enable)
{
	struct regmap *r = chip->regmap_sg;

	if (!r)
		return;

	regmap_write(r, SG_AOUTEN, (enable) ? ~0 : 0);
}