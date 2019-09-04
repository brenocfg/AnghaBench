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
struct TYPE_2__ {int /*<<< orphan*/  intrcount; } ;
struct brcmf_sdio {int dpc_triggered; int /*<<< orphan*/  datawork; int /*<<< orphan*/  brcmf_wq; int /*<<< orphan*/  intr; int /*<<< orphan*/  ipend; TYPE_1__ sdcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 scalar_t__ brcmf_sdio_intr_rstatus (struct brcmf_sdio*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void brcmf_sdio_isr(struct brcmf_sdio *bus)
{
	brcmf_dbg(TRACE, "Enter\n");

	if (!bus) {
		brcmf_err("bus is null pointer, exiting\n");
		return;
	}

	/* Count the interrupt call */
	bus->sdcnt.intrcount++;
	if (in_interrupt())
		atomic_set(&bus->ipend, 1);
	else
		if (brcmf_sdio_intr_rstatus(bus)) {
			brcmf_err("failed backplane access\n");
		}

	/* Disable additional interrupts (is this needed now)? */
	if (!bus->intr)
		brcmf_err("isr w/o interrupt configured!\n");

	bus->dpc_triggered = true;
	queue_work(bus->brcmf_wq, &bus->datawork);
}