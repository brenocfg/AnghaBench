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
 unsigned int DA9063_TWDSCALE_MASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int da9063_wdt_is_running(struct da9063 *da9063)
{
	unsigned int val;

	regmap_read(da9063->regmap, DA9063_REG_CONTROL_D, &val);

	return val & DA9063_TWDSCALE_MASK;
}