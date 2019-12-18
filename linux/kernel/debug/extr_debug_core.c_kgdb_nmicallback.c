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
struct kgdb_state {int cpu; void* linux_regs; } ;
struct TYPE_2__ {int rounding_up; scalar_t__ enter_kgdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCPU_IS_SLAVE ; 
 int /*<<< orphan*/  dbg_master_lock ; 
 int /*<<< orphan*/  kgdb_cpu_enter (struct kgdb_state*,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kgdb_info ; 
 int /*<<< orphan*/  memset (struct kgdb_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ raw_spin_is_locked (int /*<<< orphan*/ *) ; 

int kgdb_nmicallback(int cpu, void *regs)
{
#ifdef CONFIG_SMP
	struct kgdb_state kgdb_var;
	struct kgdb_state *ks = &kgdb_var;

	kgdb_info[cpu].rounding_up = false;

	memset(ks, 0, sizeof(struct kgdb_state));
	ks->cpu			= cpu;
	ks->linux_regs		= regs;

	if (kgdb_info[ks->cpu].enter_kgdb == 0 &&
			raw_spin_is_locked(&dbg_master_lock)) {
		kgdb_cpu_enter(ks, regs, DCPU_IS_SLAVE);
		return 0;
	}
#endif
	return 1;
}