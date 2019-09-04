#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct ahc_softc {int tqinfifonext; int features; int seqctl; } ;

/* Variables and functions */
 int AHC_CMD_CHAN ; 
 int BITBUCKET ; 
 int /*<<< orphan*/  CCSCBCNT ; 
 int /*<<< orphan*/  CCSCBCTL ; 
 int /*<<< orphan*/  CCSGCTL ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRSEQINT ; 
 int DIAGLEDEN ; 
 int DIAGLEDON ; 
 int ENAUTOATNP ; 
 int ENRSELI ; 
 int ENSELI ; 
 int /*<<< orphan*/  LASTPHASE ; 
 int MSG_NOOP ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int /*<<< orphan*/  MWI_RESIDUAL ; 
 int P_BUSFREE ; 
 int /*<<< orphan*/  SAVED_LUN ; 
 int /*<<< orphan*/  SAVED_SCSIID ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int SCB_DMA ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISEQ_TEMPLATE ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  SEQADDR0 ; 
 int /*<<< orphan*/  SEQADDR1 ; 
 int /*<<< orphan*/  SEQCTL ; 
 int /*<<< orphan*/  SEQ_FLAGS2 ; 
 int /*<<< orphan*/  SXFRCTL1 ; 
 int /*<<< orphan*/  TQINPOS ; 
 int /*<<< orphan*/  ahc_add_curscb_to_free_list (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_clear_msg_state (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 

__attribute__((used)) static void
ahc_restart(struct ahc_softc *ahc)
{
	uint8_t	sblkctl;

	ahc_pause(ahc);

	/* No more pending messages. */
	ahc_clear_msg_state(ahc);

	ahc_outb(ahc, SCSISIGO, 0);		/* De-assert BSY */
	ahc_outb(ahc, MSG_OUT, MSG_NOOP);	/* No message to send */
	ahc_outb(ahc, SXFRCTL1, ahc_inb(ahc, SXFRCTL1) & ~BITBUCKET);
	ahc_outb(ahc, LASTPHASE, P_BUSFREE);
	ahc_outb(ahc, SAVED_SCSIID, 0xFF);
	ahc_outb(ahc, SAVED_LUN, 0xFF);

	/*
	 * Ensure that the sequencer's idea of TQINPOS
	 * matches our own.  The sequencer increments TQINPOS
	 * only after it sees a DMA complete and a reset could
	 * occur before the increment leaving the kernel to believe
	 * the command arrived but the sequencer to not.
	 */
	ahc_outb(ahc, TQINPOS, ahc->tqinfifonext);

	/* Always allow reselection */
	ahc_outb(ahc, SCSISEQ,
		 ahc_inb(ahc, SCSISEQ_TEMPLATE) & (ENSELI|ENRSELI|ENAUTOATNP));
	if ((ahc->features & AHC_CMD_CHAN) != 0) {
		/* Ensure that no DMA operations are in progress */
		ahc_outb(ahc, CCSCBCNT, 0);
		ahc_outb(ahc, CCSGCTL, 0);
		ahc_outb(ahc, CCSCBCTL, 0);
	}
	/*
	 * If we were in the process of DMA'ing SCB data into
	 * an SCB, replace that SCB on the free list.  This prevents
	 * an SCB leak.
	 */
	if ((ahc_inb(ahc, SEQ_FLAGS2) & SCB_DMA) != 0) {
		ahc_add_curscb_to_free_list(ahc);
		ahc_outb(ahc, SEQ_FLAGS2,
			 ahc_inb(ahc, SEQ_FLAGS2) & ~SCB_DMA);
	}

	/*
	 * Clear any pending sequencer interrupt.  It is no
	 * longer relevant since we're resetting the Program
	 * Counter.
	 */
	ahc_outb(ahc, CLRINT, CLRSEQINT);

	ahc_outb(ahc, MWI_RESIDUAL, 0);
	ahc_outb(ahc, SEQCTL, ahc->seqctl);
	ahc_outb(ahc, SEQADDR0, 0);
	ahc_outb(ahc, SEQADDR1, 0);

	/*
	 * Take the LED out of diagnostic mode on PM resume, too
	 */
	sblkctl = ahc_inb(ahc, SBLKCTL);
	ahc_outb(ahc, SBLKCTL, (sblkctl & ~(DIAGLEDEN|DIAGLEDON)));

	ahc_unpause(ahc);
}