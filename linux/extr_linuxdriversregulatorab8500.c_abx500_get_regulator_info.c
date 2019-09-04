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
struct ab8500 {int dummy; } ;
struct TYPE_2__ {void* match_size; void* match; int /*<<< orphan*/  init_size; int /*<<< orphan*/  init; void* info_size; void* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_NUM_REGULATOR_REGISTERS ; 
 int /*<<< orphan*/  AB8505_NUM_REGULATOR_REGISTERS ; 
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  ab8500_reg_init ; 
 void* ab8500_regulator_info ; 
 void* ab8500_regulator_match ; 
 int /*<<< orphan*/  ab8505_reg_init ; 
 void* ab8505_regulator_info ; 
 void* ab8505_regulator_match ; 
 TYPE_1__ abx500_regulator ; 
 scalar_t__ is_ab8505 (struct ab8500*) ; 

__attribute__((used)) static void abx500_get_regulator_info(struct ab8500 *ab8500)
{
	if (is_ab8505(ab8500)) {
		abx500_regulator.info = ab8505_regulator_info;
		abx500_regulator.info_size = ARRAY_SIZE(ab8505_regulator_info);
		abx500_regulator.init = ab8505_reg_init;
		abx500_regulator.init_size = AB8505_NUM_REGULATOR_REGISTERS;
		abx500_regulator.match = ab8505_regulator_match;
		abx500_regulator.match_size = ARRAY_SIZE(ab8505_regulator_match);
	} else {
		abx500_regulator.info = ab8500_regulator_info;
		abx500_regulator.info_size = ARRAY_SIZE(ab8500_regulator_info);
		abx500_regulator.init = ab8500_reg_init;
		abx500_regulator.init_size = AB8500_NUM_REGULATOR_REGISTERS;
		abx500_regulator.match = ab8500_regulator_match;
		abx500_regulator.match_size = ARRAY_SIZE(ab8500_regulator_match);
	}
}