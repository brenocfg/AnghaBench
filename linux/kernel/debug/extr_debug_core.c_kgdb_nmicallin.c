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
struct kgdb_state {int cpu; int ex_vector; int err_code; int /*<<< orphan*/ * send_ready; void* linux_regs; int /*<<< orphan*/  signo; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {scalar_t__ enter_kgdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCPU_WANT_MASTER ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  kgdb_cpu_enter (struct kgdb_state*,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kgdb_info ; 
 int /*<<< orphan*/  kgdb_io_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kgdb_state*,int /*<<< orphan*/ ,int) ; 

int kgdb_nmicallin(int cpu, int trapnr, void *regs, int err_code,
							atomic_t *send_ready)
{
#ifdef CONFIG_SMP
	if (!kgdb_io_ready(0) || !send_ready)
		return 1;

	if (kgdb_info[cpu].enter_kgdb == 0) {
		struct kgdb_state kgdb_var;
		struct kgdb_state *ks = &kgdb_var;

		memset(ks, 0, sizeof(struct kgdb_state));
		ks->cpu			= cpu;
		ks->ex_vector		= trapnr;
		ks->signo		= SIGTRAP;
		ks->err_code		= err_code;
		ks->linux_regs		= regs;
		ks->send_ready		= send_ready;
		kgdb_cpu_enter(ks, regs, DCPU_WANT_MASTER);
		return 0;
	}
#endif
	return 1;
}