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
struct kgdb_state {size_t cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  debuggerinfo; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdb_current_regs ; 
 int /*<<< orphan*/  kdb_current_task ; 
 int /*<<< orphan*/  kdb_initial_cpu ; 
 int /*<<< orphan*/  kgdb_active ; 
 TYPE_1__* kgdb_info ; 

int kdb_common_init_state(struct kgdb_state *ks)
{
	kdb_initial_cpu = atomic_read(&kgdb_active);
	kdb_current_task = kgdb_info[ks->cpu].task;
	kdb_current_regs = kgdb_info[ks->cpu].debuggerinfo;
	return 0;
}