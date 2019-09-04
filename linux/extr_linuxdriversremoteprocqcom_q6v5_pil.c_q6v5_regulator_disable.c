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
struct reg_info {scalar_t__ uV; scalar_t__ uA; int /*<<< orphan*/  reg; } ;
struct q6v5 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void q6v5_regulator_disable(struct q6v5 *qproc,
				   struct reg_info *regs, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		if (regs[i].uV > 0)
			regulator_set_voltage(regs[i].reg, 0, INT_MAX);

		if (regs[i].uA > 0)
			regulator_set_load(regs[i].reg, 0);

		regulator_disable(regs[i].reg);
	}
}