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
struct ips_driver {int orig_turbo_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  THM_MPCPC ; 
 int /*<<< orphan*/  TURBO_POWER_CURRENT_LIMIT ; 
 int TURBO_TDC_OVR_EN ; 
 int TURBO_TDP_MASK ; 
 int TURBO_TDP_OVR_EN ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thm_writew (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ips_cpu_lower(struct ips_driver *ips)
{
	u64 turbo_override;
	u16 cur_limit, new_limit;

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	cur_limit = turbo_override & TURBO_TDP_MASK;
	new_limit = cur_limit - 8; /* 1W decrease */

	/* Clamp to SKU TDP limit */
	if (new_limit  < (ips->orig_turbo_limit & TURBO_TDP_MASK))
		new_limit = ips->orig_turbo_limit & TURBO_TDP_MASK;

	thm_writew(THM_MPCPC, (new_limit * 10) / 8);

	turbo_override |= TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN;
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	turbo_override &= ~TURBO_TDP_MASK;
	turbo_override |= new_limit;

	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
}