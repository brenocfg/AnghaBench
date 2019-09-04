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
typedef  int u64 ;
typedef  int u32 ;
struct rapl_package {int energy_unit; int power_unit; int time_unit; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENERGY_UNIT_MASK ; 
 int ENERGY_UNIT_OFFSET ; 
 int ENERGY_UNIT_SCALE ; 
 int ENODEV ; 
 int /*<<< orphan*/  MSR_RAPL_POWER_UNIT ; 
 int POWER_UNIT_MASK ; 
 int POWER_UNIT_OFFSET ; 
 int TIME_UNIT_MASK ; 
 int TIME_UNIT_OFFSET ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdmsrl_safe_on_cpu (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rapl_check_unit_core(struct rapl_package *rp, int cpu)
{
	u64 msr_val;
	u32 value;

	if (rdmsrl_safe_on_cpu(cpu, MSR_RAPL_POWER_UNIT, &msr_val)) {
		pr_err("Failed to read power unit MSR 0x%x on CPU %d, exit.\n",
			MSR_RAPL_POWER_UNIT, cpu);
		return -ENODEV;
	}

	value = (msr_val & ENERGY_UNIT_MASK) >> ENERGY_UNIT_OFFSET;
	rp->energy_unit = ENERGY_UNIT_SCALE * 1000000 / (1 << value);

	value = (msr_val & POWER_UNIT_MASK) >> POWER_UNIT_OFFSET;
	rp->power_unit = 1000000 / (1 << value);

	value = (msr_val & TIME_UNIT_MASK) >> TIME_UNIT_OFFSET;
	rp->time_unit = 1000000 / (1 << value);

	pr_debug("Core CPU package %d energy=%dpJ, time=%dus, power=%duW\n",
		rp->id, rp->energy_unit, rp->time_unit, rp->power_unit);

	return 0;
}