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
struct adp5061_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5061_CHG_CURR ; 
 int /*<<< orphan*/  ADP5061_CHG_CURR_ICHG_MODE (int) ; 
 int /*<<< orphan*/  ADP5061_CHG_CURR_ICHG_MSK ; 
 int ADP5061_ICHG_MAX ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp5061_const_ichg ; 
 int adp5061_get_array_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adp5061_set_const_chg_current(struct adp5061_state *st, int val)
{

	int index;

	/* Convert from uA to mA */
	val /= 1000;
	if (val > ADP5061_ICHG_MAX)
		val = ADP5061_ICHG_MAX;

	index = adp5061_get_array_index(adp5061_const_ichg,
					ARRAY_SIZE(adp5061_const_ichg),
					val);
	if (index < 0)
		return index;

	return regmap_update_bits(st->regmap, ADP5061_CHG_CURR,
				  ADP5061_CHG_CURR_ICHG_MSK,
				  ADP5061_CHG_CURR_ICHG_MODE(index));
}