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
struct i2c_client {int dummy; } ;
struct cs35l36_private {int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; scalar_t__ reset_gpio; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L36_INT1_MASK ; 
 int /*<<< orphan*/  CS35L36_INT1_MASK_RESET ; 
 int /*<<< orphan*/  CS35L36_INT3_MASK ; 
 int /*<<< orphan*/  CS35L36_INT3_MASK_RESET ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 struct cs35l36_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l36_i2c_remove(struct i2c_client *client)
{
	struct cs35l36_private *cs35l36 = i2c_get_clientdata(client);

	/* Reset interrupt masks for device removal */
	regmap_write(cs35l36->regmap, CS35L36_INT1_MASK,
		     CS35L36_INT1_MASK_RESET);
	regmap_write(cs35l36->regmap, CS35L36_INT3_MASK,
		     CS35L36_INT3_MASK_RESET);

	if (cs35l36->reset_gpio)
		gpiod_set_value_cansleep(cs35l36->reset_gpio, 0);

	regulator_bulk_disable(cs35l36->num_supplies, cs35l36->supplies);

	return 0;
}