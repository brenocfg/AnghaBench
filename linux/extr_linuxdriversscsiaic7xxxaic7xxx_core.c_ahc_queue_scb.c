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
struct scb {TYPE_1__* hscb; } ;
struct ahc_softc {scalar_t__* qinfifo; int features; int /*<<< orphan*/  qinfifonext; } ;
struct TYPE_2__ {scalar_t__ tag; scalar_t__ next; int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int AHC_AUTOPAUSE ; 
 int AHC_QUEUE_REGS ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  HNSCB_QOFF ; 
 int /*<<< orphan*/  KERNEL_QINPOS ; 
 int /*<<< orphan*/  LID ; 
 scalar_t__ SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_XFERLEN_ODD ; 
 int ahc_get_transfer_length (struct scb*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_swap_with_next_hscb (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahc_sync_scb (struct ahc_softc*,struct scb*,int) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,scalar_t__) ; 

void
ahc_queue_scb(struct ahc_softc *ahc, struct scb *scb)
{
	ahc_swap_with_next_hscb(ahc, scb);

	if (scb->hscb->tag == SCB_LIST_NULL
	 || scb->hscb->next == SCB_LIST_NULL)
		panic("Attempt to queue invalid SCB tag %x:%x\n",
		      scb->hscb->tag, scb->hscb->next);

	/*
	 * Setup data "oddness".
	 */
	scb->hscb->lun &= LID;
	if (ahc_get_transfer_length(scb) & 0x1)
		scb->hscb->lun |= SCB_XFERLEN_ODD;

	/*
	 * Keep a history of SCBs we've downloaded in the qinfifo.
	 */
	ahc->qinfifo[ahc->qinfifonext++] = scb->hscb->tag;

	/*
	 * Make sure our data is consistent from the
	 * perspective of the adapter.
	 */
	ahc_sync_scb(ahc, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);

	/* Tell the adapter about the newly queued SCB */
	if ((ahc->features & AHC_QUEUE_REGS) != 0) {
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfifonext);
	} else {
		if ((ahc->features & AHC_AUTOPAUSE) == 0)
			ahc_pause(ahc);
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfifonext);
		if ((ahc->features & AHC_AUTOPAUSE) == 0)
			ahc_unpause(ahc);
	}
}