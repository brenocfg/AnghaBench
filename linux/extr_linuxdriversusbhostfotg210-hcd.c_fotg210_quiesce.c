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
typedef  int u32 ;
struct fotg210_hcd {scalar_t__ rh_state; int command; TYPE_1__* regs; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_ASE ; 
 int CMD_PSE ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 int STS_ASS ; 
 int STS_PSS ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handshake (struct fotg210_hcd*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_quiesce(struct fotg210_hcd *fotg210)
{
	u32 temp;

	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;

	/* wait for any schedule enables/disables to take effect */
	temp = (fotg210->command << 10) & (STS_ASS | STS_PSS);
	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, temp,
			16 * 125);

	/* then disable anything that's still active */
	spin_lock_irq(&fotg210->lock);
	fotg210->command &= ~(CMD_ASE | CMD_PSE);
	fotg210_writel(fotg210, fotg210->command, &fotg210->regs->command);
	spin_unlock_irq(&fotg210->lock);

	/* hardware can take 16 microframes to turn off ... */
	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, 0,
			16 * 125);
}