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
struct TYPE_4__ {int /*<<< orphan*/  DriverLock; scalar_t__ ResetRequested; } ;
struct TYPE_3__ {int is_imask; } ;
struct s_smc {TYPE_2__ os; TYPE_1__ hw; } ;
struct net_device {int dummy; } ;
typedef  TYPE_2__ skfddi_priv ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  CLI_FBI () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR_A ; 
 int /*<<< orphan*/  ResetAdapter (struct s_smc*) ; 
 int /*<<< orphan*/  STI_FBI () ; 
 int /*<<< orphan*/  fddi_isr (struct s_smc*) ; 
 int inpd (int /*<<< orphan*/ ) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t skfp_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct s_smc *smc;	/* private board structure pointer */
	skfddi_priv *bp;

	smc = netdev_priv(dev);
	bp = &smc->os;

	// IRQs enabled or disabled ?
	if (inpd(ADDR(B0_IMSK)) == 0) {
		// IRQs are disabled: must be shared interrupt
		return IRQ_NONE;
	}
	// Note: At this point, IRQs are enabled.
	if ((inpd(ISR_A) & smc->hw.is_imask) == 0) {	// IRQ?
		// Adapter did not issue an IRQ: must be shared interrupt
		return IRQ_NONE;
	}
	CLI_FBI();		// Disable IRQs from our adapter.
	spin_lock(&bp->DriverLock);

	// Call interrupt handler in hardware module (HWM).
	fddi_isr(smc);

	if (smc->os.ResetRequested) {
		ResetAdapter(smc);
		smc->os.ResetRequested = FALSE;
	}
	spin_unlock(&bp->DriverLock);
	STI_FBI();		// Enable IRQs from our adapter.

	return IRQ_HANDLED;
}