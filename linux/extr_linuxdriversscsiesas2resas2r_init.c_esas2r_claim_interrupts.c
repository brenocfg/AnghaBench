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
struct esas2r_adapter {scalar_t__ intr_mode; TYPE_1__* pcid; int /*<<< orphan*/  flags2; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_IRQ_CLAIMED ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 scalar_t__ INTR_MODE_LEGACY ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  esas2r_interrupt ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  esas2r_msi_interrupt ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_claim_interrupts(struct esas2r_adapter *a)
{
	unsigned long flags = 0;

	if (a->intr_mode == INTR_MODE_LEGACY)
		flags |= IRQF_SHARED;

	esas2r_log(ESAS2R_LOG_INFO,
		   "esas2r_claim_interrupts irq=%d (%p, %s, %lx)",
		   a->pcid->irq, a, a->name, flags);

	if (request_irq(a->pcid->irq,
			(a->intr_mode ==
			 INTR_MODE_LEGACY) ? esas2r_interrupt :
			esas2r_msi_interrupt,
			flags,
			a->name,
			a)) {
		esas2r_log(ESAS2R_LOG_CRIT, "unable to request IRQ %02X",
			   a->pcid->irq);
		return;
	}

	set_bit(AF2_IRQ_CLAIMED, &a->flags2);
	esas2r_log(ESAS2R_LOG_INFO,
		   "claimed IRQ %d flags: 0x%lx",
		   a->pcid->irq, flags);
}