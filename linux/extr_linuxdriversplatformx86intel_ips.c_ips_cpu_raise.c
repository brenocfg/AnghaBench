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
typedef  int u16 ;
struct ips_driver {int core_power_limit; int /*<<< orphan*/  cpu_turbo_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  THM_MPCPC ; 
 int /*<<< orphan*/  TURBO_POWER_CURRENT_LIMIT ; 
 int TURBO_TDC_OVR_EN ; 
 int TURBO_TDP_MASK ; 
 int TURBO_TDP_OVR_EN ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thm_writew (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ips_cpu_raise(struct ips_driver *ips)
{
	u64 turbo_override;
	u16 cur_tdp_limit, new_tdp_limit;

	if (!ips->cpu_turbo_enabled)
		return;

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	cur_tdp_limit = turbo_override & TURBO_TDP_MASK;
	new_tdp_limit = cur_tdp_limit + 8; /* 1W increase */

	/* Clamp to SKU TDP limit */
	if (((new_tdp_limit * 10) / 8) > ips->core_power_limit)
		new_tdp_limit = cur_tdp_limit;

	thm_writew(THM_MPCPC, (new_tdp_limit * 10) / 8);

	turbo_override |= TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN;
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	turbo_override &= ~TURBO_TDP_MASK;
	turbo_override |= new_tdp_limit;

	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
}