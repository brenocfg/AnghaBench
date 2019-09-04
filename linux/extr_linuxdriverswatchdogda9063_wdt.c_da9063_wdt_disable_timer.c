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
struct da9063 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9063_REG_CONTROL_D ; 
 int /*<<< orphan*/  DA9063_TWDSCALE_DISABLE ; 
 int /*<<< orphan*/  DA9063_TWDSCALE_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9063_wdt_disable_timer(struct da9063 *da9063)
{
	return regmap_update_bits(da9063->regmap, DA9063_REG_CONTROL_D,
				  DA9063_TWDSCALE_MASK,
				  DA9063_TWDSCALE_DISABLE);
}