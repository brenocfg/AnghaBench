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
struct qoriq_ptp_registers {TYPE_1__* ctrl_regs; } ;
struct qoriq_ptp {int /*<<< orphan*/  irq; int /*<<< orphan*/  rsrc; int /*<<< orphan*/  base; int /*<<< orphan*/  clock; struct qoriq_ptp_registers regs; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_ctrl; int /*<<< orphan*/  tmr_temask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qoriq_ptp*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qoriq_ptp*) ; 
 struct qoriq_ptp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qoriq_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qoriq_ptp_remove(struct platform_device *dev)
{
	struct qoriq_ptp *qoriq_ptp = platform_get_drvdata(dev);
	struct qoriq_ptp_registers *regs = &qoriq_ptp->regs;

	qoriq_write(&regs->ctrl_regs->tmr_temask, 0);
	qoriq_write(&regs->ctrl_regs->tmr_ctrl,   0);

	ptp_clock_unregister(qoriq_ptp->clock);
	iounmap(qoriq_ptp->base);
	release_resource(qoriq_ptp->rsrc);
	free_irq(qoriq_ptp->irq, qoriq_ptp);
	kfree(qoriq_ptp);

	return 0;
}