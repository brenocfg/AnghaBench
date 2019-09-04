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
typedef  int u_int ;
struct scb {int /*<<< orphan*/  flags; } ;
struct ahc_softc {int msgout_len; int /*<<< orphan*/  msg_type; scalar_t__ msgout_index; int /*<<< orphan*/ * msgout_buf; } ;
struct ahc_devinfo {int dummy; } ;
struct TYPE_2__ {int phasemsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_SEQUENCE_FAIL ; 
 int ENSELO ; 
 int HOST_MSG ; 
 int /*<<< orphan*/  LASTPHASE ; 
 int /*<<< orphan*/  MSG_ABORT_TASK ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int /*<<< orphan*/  MSG_TYPE_INITIATOR_MSGOUT ; 
 int NOT_IDENTIFIED ; 
 int NO_CDB_SENT ; 
 int PHASE_MASK ; 
 int P_COMMAND ; 
 int P_DATAIN_DT ; 
 int /*<<< orphan*/  SCB_ABORT ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int /*<<< orphan*/  SCB_TAG ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISIGI ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int STATUS_RCVD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahc_assert_atn (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_dump_card_state (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_fetch_devinfo (struct ahc_softc*,struct ahc_devinfo*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ahc_lookup_phase_entry (int) ; 
 struct scb* ahc_lookup_scb (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_print_devinfo (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  ahc_print_path (struct ahc_softc*,struct scb*) ; 
 int ahc_reset_channel (struct ahc_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
ahc_handle_proto_violation(struct ahc_softc *ahc)
{
	struct	ahc_devinfo devinfo;
	struct	scb *scb;
	u_int	scbid;
	u_int	seq_flags;
	u_int	curphase;
	u_int	lastphase;
	int	found;

	ahc_fetch_devinfo(ahc, &devinfo);
	scbid = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scbid);
	seq_flags = ahc_inb(ahc, SEQ_FLAGS);
	curphase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;
	lastphase = ahc_inb(ahc, LASTPHASE);
	if ((seq_flags & NOT_IDENTIFIED) != 0) {

		/*
		 * The reconnecting target either did not send an
		 * identify message, or did, but we didn't find an SCB
		 * to match.
		 */
		ahc_print_devinfo(ahc, &devinfo);
		printk("Target did not send an IDENTIFY message. "
		       "LASTPHASE = 0x%x.\n", lastphase);
		scb = NULL;
	} else if (scb == NULL) {
		/*
		 * We don't seem to have an SCB active for this
		 * transaction.  Print an error and reset the bus.
		 */
		ahc_print_devinfo(ahc, &devinfo);
		printk("No SCB found during protocol violation\n");
		goto proto_violation_reset;
	} else {
		ahc_set_transaction_status(scb, CAM_SEQUENCE_FAIL);
		if ((seq_flags & NO_CDB_SENT) != 0) {
			ahc_print_path(ahc, scb);
			printk("No or incomplete CDB sent to device.\n");
		} else if ((ahc_inb(ahc, SCB_CONTROL) & STATUS_RCVD) == 0) {
			/*
			 * The target never bothered to provide status to
			 * us prior to completing the command.  Since we don't
			 * know the disposition of this command, we must attempt
			 * to abort it.  Assert ATN and prepare to send an abort
			 * message.
			 */
			ahc_print_path(ahc, scb);
			printk("Completed command without status.\n");
		} else {
			ahc_print_path(ahc, scb);
			printk("Unknown protocol violation.\n");
			ahc_dump_card_state(ahc);
		}
	}
	if ((lastphase & ~P_DATAIN_DT) == 0
	 || lastphase == P_COMMAND) {
proto_violation_reset:
		/*
		 * Target either went directly to data/command
		 * phase or didn't respond to our ATN.
		 * The only safe thing to do is to blow
		 * it away with a bus reset.
		 */
		found = ahc_reset_channel(ahc, 'A', TRUE);
		printk("%s: Issued Channel %c Bus Reset. "
		       "%d SCBs aborted\n", ahc_name(ahc), 'A', found);
	} else {
		/*
		 * Leave the selection hardware off in case
		 * this abort attempt will affect yet to
		 * be sent commands.
		 */
		ahc_outb(ahc, SCSISEQ,
			 ahc_inb(ahc, SCSISEQ) & ~ENSELO);
		ahc_assert_atn(ahc);
		ahc_outb(ahc, MSG_OUT, HOST_MSG);
		if (scb == NULL) {
			ahc_print_devinfo(ahc, &devinfo);
			ahc->msgout_buf[0] = MSG_ABORT_TASK;
			ahc->msgout_len = 1;
			ahc->msgout_index = 0;
			ahc->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		} else {
			ahc_print_path(ahc, scb);
			scb->flags |= SCB_ABORT;
		}
		printk("Protocol violation %s.  Attempting to abort.\n",
		       ahc_lookup_phase_entry(curphase)->phasemsg);
	}
}