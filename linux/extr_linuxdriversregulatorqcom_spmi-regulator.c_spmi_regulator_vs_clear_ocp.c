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
struct spmi_regulator {int /*<<< orphan*/  vs_enable_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_DISABLE ; 
 int /*<<< orphan*/  SPMI_COMMON_ENABLE ; 
 int /*<<< orphan*/  SPMI_COMMON_ENABLE_MASK ; 
 int /*<<< orphan*/  SPMI_COMMON_REG_ENABLE ; 
 int /*<<< orphan*/  ktime_get () ; 
 int spmi_vreg_update_bits (struct spmi_regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spmi_regulator_vs_clear_ocp(struct spmi_regulator *vreg)
{
	int ret;

	ret = spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_ENABLE,
		SPMI_COMMON_DISABLE, SPMI_COMMON_ENABLE_MASK);

	vreg->vs_enable_time = ktime_get();

	ret = spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_ENABLE,
		SPMI_COMMON_ENABLE, SPMI_COMMON_ENABLE_MASK);

	return ret;
}