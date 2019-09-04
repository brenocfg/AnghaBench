#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rapl_primitive_info {int flag; size_t id; int mask; int shift; int /*<<< orphan*/  unit; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int* primitives; } ;
struct rapl_domain {scalar_t__ id; TYPE_2__ rdd; TYPE_1__* rp; int /*<<< orphan*/ * msrs; } ;
typedef  enum rapl_primitives { ____Placeholder_rapl_primitives } rapl_primitives ;
struct TYPE_3__ {int lead_cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int FW_LOCK ; 
 int POWER_PACKAGE_LOCK ; 
 scalar_t__ RAPL_DOMAIN_PACKAGE ; 
 int RAPL_PRIMITIVE_DERIVED ; 
 int RAPL_PRIMITIVE_DUMMY ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int rapl_unit_xlate (struct rapl_domain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rdmsrl_safe_on_cpu (int,int /*<<< orphan*/ ,int*) ; 
 struct rapl_primitive_info* rpi ; 

__attribute__((used)) static int rapl_read_data_raw(struct rapl_domain *rd,
			enum rapl_primitives prim,
			bool xlate, u64 *data)
{
	u64 value, final;
	u32 msr;
	struct rapl_primitive_info *rp = &rpi[prim];
	int cpu;

	if (!rp->name || rp->flag & RAPL_PRIMITIVE_DUMMY)
		return -EINVAL;

	msr = rd->msrs[rp->id];
	if (!msr)
		return -EINVAL;

	cpu = rd->rp->lead_cpu;

	/* special-case package domain, which uses a different bit*/
	if (prim == FW_LOCK && rd->id == RAPL_DOMAIN_PACKAGE) {
		rp->mask = POWER_PACKAGE_LOCK;
		rp->shift = 63;
	}
	/* non-hardware data are collected by the polling thread */
	if (rp->flag & RAPL_PRIMITIVE_DERIVED) {
		*data = rd->rdd.primitives[prim];
		return 0;
	}

	if (rdmsrl_safe_on_cpu(cpu, msr, &value)) {
		pr_debug("failed to read msr 0x%x on cpu %d\n", msr, cpu);
		return -EIO;
	}

	final = value & rp->mask;
	final = final >> rp->shift;
	if (xlate)
		*data = rapl_unit_xlate(rd, rp->unit, final, 0);
	else
		*data = final;

	return 0;
}