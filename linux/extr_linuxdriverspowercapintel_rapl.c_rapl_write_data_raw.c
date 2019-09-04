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
typedef  int /*<<< orphan*/  u64 ;
struct rapl_primitive_info {size_t id; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  unit; } ;
struct rapl_domain {int /*<<< orphan*/ * msrs; TYPE_1__* rp; } ;
struct msrl_action {int err; int /*<<< orphan*/  set_mask; int /*<<< orphan*/  clear_mask; int /*<<< orphan*/  msr_no; } ;
typedef  int /*<<< orphan*/  ma ;
typedef  enum rapl_primitives { ____Placeholder_rapl_primitives } rapl_primitives ;
struct TYPE_2__ {int lead_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (struct msrl_action*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msrl_update_func ; 
 int /*<<< orphan*/  rapl_unit_xlate (struct rapl_domain*,int /*<<< orphan*/ ,unsigned long long,int) ; 
 struct rapl_primitive_info* rpi ; 
 int smp_call_function_single (int,int /*<<< orphan*/ ,struct msrl_action*,int) ; 

__attribute__((used)) static int rapl_write_data_raw(struct rapl_domain *rd,
			enum rapl_primitives prim,
			unsigned long long value)
{
	struct rapl_primitive_info *rp = &rpi[prim];
	int cpu;
	u64 bits;
	struct msrl_action ma;
	int ret;

	cpu = rd->rp->lead_cpu;
	bits = rapl_unit_xlate(rd, rp->unit, value, 1);
	bits <<= rp->shift;
	bits &= rp->mask;

	memset(&ma, 0, sizeof(ma));

	ma.msr_no = rd->msrs[rp->id];
	ma.clear_mask = rp->mask;
	ma.set_mask = bits;

	ret = smp_call_function_single(cpu, msrl_update_func, &ma, 1);
	if (ret)
		WARN_ON_ONCE(ret);
	else
		ret = ma.err;

	return ret;
}