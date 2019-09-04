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
struct qoriq_ptp_registers {TYPE_1__* fiper_regs; } ;
struct qoriq_ptp {int /*<<< orphan*/  tmr_fiper2; int /*<<< orphan*/  tmr_fiper1; struct qoriq_ptp_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_fiper2; int /*<<< orphan*/  tmr_fiper1; } ;

/* Variables and functions */
 int /*<<< orphan*/  qoriq_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_alarm (struct qoriq_ptp*) ; 

__attribute__((used)) static void set_fipers(struct qoriq_ptp *qoriq_ptp)
{
	struct qoriq_ptp_registers *regs = &qoriq_ptp->regs;

	set_alarm(qoriq_ptp);
	qoriq_write(&regs->fiper_regs->tmr_fiper1, qoriq_ptp->tmr_fiper1);
	qoriq_write(&regs->fiper_regs->tmr_fiper2, qoriq_ptp->tmr_fiper2);
}