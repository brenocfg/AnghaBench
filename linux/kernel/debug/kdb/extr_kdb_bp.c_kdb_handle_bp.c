#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int bp_delayed; scalar_t__ bp_delay; } ;
typedef  TYPE_1__ kdb_bp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP ; 
 scalar_t__ KDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  kdb_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_setsinglestep (struct pt_regs*) ; 

__attribute__((used)) static void kdb_handle_bp(struct pt_regs *regs, kdb_bp_t *bp)
{
	if (KDB_DEBUG(BP))
		kdb_printf("regs->ip = 0x%lx\n", instruction_pointer(regs));

	/*
	 * Setup single step
	 */
	kdb_setsinglestep(regs);

	/*
	 * Reset delay attribute
	 */
	bp->bp_delay = 0;
	bp->bp_delayed = 1;
}