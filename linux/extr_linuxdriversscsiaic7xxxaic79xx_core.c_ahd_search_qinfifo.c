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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
struct scb {int flags; } ;
struct TYPE_4__ {size_t numscbs; } ;
struct ahd_softc {size_t qinfifonext; size_t* qinfifo; TYPE_2__ scb_data; TYPE_1__* next_queued_hscb; } ;
typedef  int /*<<< orphan*/  role_t ;
typedef  int ahd_search_action ;
typedef  int /*<<< orphan*/  ahd_mode_state ;
struct TYPE_3__ {int /*<<< orphan*/  hscb_busaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_CCHAN ; 
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int AHD_NUM_TARGETS ; 
 size_t AHD_QIN_WRAP (size_t) ; 
 int CAM_LUN_WILDCARD ; 
 size_t CCARREN ; 
 int /*<<< orphan*/  CCSCBCTL ; 
 size_t CCSCBDIR ; 
 size_t CCSCBEN ; 
 size_t CMDS_PENDING ; 
 size_t MK_MESSAGE_SCB ; 
 int /*<<< orphan*/  NEXT_QUEUED_SCB_ADDR ; 
 size_t PENDING_MK_MESSAGE ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 scalar_t__ SCBID_IS_NULL (size_t) ; 
 int SCB_ACTIVE ; 
 int /*<<< orphan*/  SCB_GET_TAG (struct scb*) ; 
 int SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 size_t SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_NEXT2 ; 
#define  SEARCH_COMPLETE 131 
#define  SEARCH_COUNT 130 
#define  SEARCH_PRINT 129 
#define  SEARCH_REMOVE 128 
 int /*<<< orphan*/  SEQ_FLAGS2 ; 
 int /*<<< orphan*/  WAITING_SCB_TAILS ; 
 size_t WAITING_TID_HEAD ; 
 int /*<<< orphan*/  ahd_done_with_status (struct ahd_softc*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 size_t ahd_get_scbptr (struct ahd_softc*) ; 
 size_t ahd_get_snscb_qoff (struct ahd_softc*) ; 
 size_t ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 size_t ahd_inw (struct ahd_softc*,size_t) ; 
 size_t ahd_inw_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_le32toh (int /*<<< orphan*/ ) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,size_t) ; 
 scalar_t__ ahd_match_scb (struct ahd_softc*,struct scb*,int,char,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ahd_outl (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,size_t,size_t) ; 
 int /*<<< orphan*/  ahd_qinfifo_requeue (struct ahd_softc*,struct scb*,struct scb*) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 scalar_t__ ahd_search_scb_list (struct ahd_softc*,int,char,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,size_t*,int) ; 
 int /*<<< orphan*/  ahd_set_hnscb_qoff (struct ahd_softc*,size_t) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,size_t) ; 
 int /*<<< orphan*/  ahd_stitch_tid_list (struct ahd_softc*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int
ahd_search_qinfifo(struct ahd_softc *ahd, int target, char channel,
		   int lun, u_int tag, role_t role, uint32_t status,
		   ahd_search_action action)
{
	struct scb	*scb;
	struct scb	*mk_msg_scb;
	struct scb	*prev_scb;
	ahd_mode_state	 saved_modes;
	u_int		 qinstart;
	u_int		 qinpos;
	u_int		 qintail;
	u_int		 tid_next;
	u_int		 tid_prev;
	u_int		 scbid;
	u_int		 seq_flags2;
	u_int		 savedscbptr;
	uint32_t	 busaddr;
	int		 found;
	int		 targets;

	/* Must be in CCHAN mode */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Halt any pending SCB DMA.  The sequencer will reinitiate
	 * this dma if the qinfifo is not empty once we unpause.
	 */
	if ((ahd_inb(ahd, CCSCBCTL) & (CCARREN|CCSCBEN|CCSCBDIR))
	 == (CCARREN|CCSCBEN|CCSCBDIR)) {
		ahd_outb(ahd, CCSCBCTL,
			 ahd_inb(ahd, CCSCBCTL) & ~(CCARREN|CCSCBEN));
		while ((ahd_inb(ahd, CCSCBCTL) & (CCARREN|CCSCBEN)) != 0)
			;
	}
	/* Determine sequencer's position in the qinfifo. */
	qintail = AHD_QIN_WRAP(ahd->qinfifonext);
	qinstart = ahd_get_snscb_qoff(ahd);
	qinpos = AHD_QIN_WRAP(qinstart);
	found = 0;
	prev_scb = NULL;

	if (action == SEARCH_PRINT) {
		printk("qinstart = %d qinfifonext = %d\nQINFIFO:",
		       qinstart, ahd->qinfifonext);
	}

	/*
	 * Start with an empty queue.  Entries that are not chosen
	 * for removal will be re-added to the queue as we go.
	 */
	ahd->qinfifonext = qinstart;
	busaddr = ahd_le32toh(ahd->next_queued_hscb->hscb_busaddr);
	ahd_outl(ahd, NEXT_QUEUED_SCB_ADDR, busaddr);

	while (qinpos != qintail) {
		scb = ahd_lookup_scb(ahd, ahd->qinfifo[qinpos]);
		if (scb == NULL) {
			printk("qinpos = %d, SCB index = %d\n",
				qinpos, ahd->qinfifo[qinpos]);
			panic("Loop 1\n");
		}

		if (ahd_match_scb(ahd, scb, target, channel, lun, tag, role)) {
			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			switch (action) {
			case SEARCH_COMPLETE:
				if ((scb->flags & SCB_ACTIVE) == 0)
					printk("Inactive SCB in qinfifo\n");
				ahd_done_with_status(ahd, scb, status);
				/* FALLTHROUGH */
			case SEARCH_REMOVE:
				break;
			case SEARCH_PRINT:
				printk(" 0x%x", ahd->qinfifo[qinpos]);
				/* FALLTHROUGH */
			case SEARCH_COUNT:
				ahd_qinfifo_requeue(ahd, prev_scb, scb);
				prev_scb = scb;
				break;
			}
		} else {
			ahd_qinfifo_requeue(ahd, prev_scb, scb);
			prev_scb = scb;
		}
		qinpos = AHD_QIN_WRAP(qinpos+1);
	}

	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);

	if (action == SEARCH_PRINT)
		printk("\nWAITING_TID_QUEUES:\n");

	/*
	 * Search waiting for selection lists.  We traverse the
	 * list of "their ids" waiting for selection and, if
	 * appropriate, traverse the SCBs of each "their id"
	 * looking for matches.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	seq_flags2 = ahd_inb(ahd, SEQ_FLAGS2);
	if ((seq_flags2 & PENDING_MK_MESSAGE) != 0) {
		scbid = ahd_inw(ahd, MK_MESSAGE_SCB);
		mk_msg_scb = ahd_lookup_scb(ahd, scbid);
	} else
		mk_msg_scb = NULL;
	savedscbptr = ahd_get_scbptr(ahd);
	tid_next = ahd_inw(ahd, WAITING_TID_HEAD);
	tid_prev = SCB_LIST_NULL;
	targets = 0;
	for (scbid = tid_next; !SCBID_IS_NULL(scbid); scbid = tid_next) {
		u_int tid_head;
		u_int tid_tail;

		targets++;
		if (targets > AHD_NUM_TARGETS)
			panic("TID LIST LOOP");

		if (scbid >= ahd->scb_data.numscbs) {
			printk("%s: Waiting TID List inconsistency. "
			       "SCB index == 0x%x, yet numscbs == 0x%x.",
			       ahd_name(ahd), scbid, ahd->scb_data.numscbs);
			ahd_dump_card_state(ahd);
			panic("for safety");
		}
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb == NULL) {
			printk("%s: SCB = 0x%x Not Active!\n",
			       ahd_name(ahd), scbid);
			panic("Waiting TID List traversal\n");
		}
		ahd_set_scbptr(ahd, scbid);
		tid_next = ahd_inw_scbram(ahd, SCB_NEXT2);
		if (ahd_match_scb(ahd, scb, target, channel, CAM_LUN_WILDCARD,
				  SCB_LIST_NULL, ROLE_UNKNOWN) == 0) {
			tid_prev = scbid;
			continue;
		}

		/*
		 * We found a list of scbs that needs to be searched.
		 */
		if (action == SEARCH_PRINT)
			printk("       %d ( ", SCB_GET_TARGET(ahd, scb));
		tid_head = scbid;
		found += ahd_search_scb_list(ahd, target, channel,
					     lun, tag, role, status,
					     action, &tid_head, &tid_tail,
					     SCB_GET_TARGET(ahd, scb));
		/*
		 * Check any MK_MESSAGE SCB that is still waiting to
		 * enter this target's waiting for selection queue.
		 */
		if (mk_msg_scb != NULL
		 && ahd_match_scb(ahd, mk_msg_scb, target, channel,
				  lun, tag, role)) {

			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			switch (action) {
			case SEARCH_COMPLETE:
				if ((mk_msg_scb->flags & SCB_ACTIVE) == 0)
					printk("Inactive SCB pending MK_MSG\n");
				ahd_done_with_status(ahd, mk_msg_scb, status);
				/* FALLTHROUGH */
			case SEARCH_REMOVE:
			{
				u_int tail_offset;

				printk("Removing MK_MSG scb\n");

				/*
				 * Reset our tail to the tail of the
				 * main per-target list.
				 */
				tail_offset = WAITING_SCB_TAILS
				    + (2 * SCB_GET_TARGET(ahd, mk_msg_scb));
				ahd_outw(ahd, tail_offset, tid_tail);

				seq_flags2 &= ~PENDING_MK_MESSAGE;
				ahd_outb(ahd, SEQ_FLAGS2, seq_flags2);
				ahd_outw(ahd, CMDS_PENDING,
					 ahd_inw(ahd, CMDS_PENDING)-1);
				mk_msg_scb = NULL;
				break;
			}
			case SEARCH_PRINT:
				printk(" 0x%x", SCB_GET_TAG(scb));
				/* FALLTHROUGH */
			case SEARCH_COUNT:
				break;
			}
		}

		if (mk_msg_scb != NULL
		 && SCBID_IS_NULL(tid_head)
		 && ahd_match_scb(ahd, scb, target, channel, CAM_LUN_WILDCARD,
				  SCB_LIST_NULL, ROLE_UNKNOWN)) {

			/*
			 * When removing the last SCB for a target
			 * queue with a pending MK_MESSAGE scb, we
			 * must queue the MK_MESSAGE scb.
			 */
			printk("Queueing mk_msg_scb\n");
			tid_head = ahd_inw(ahd, MK_MESSAGE_SCB);
			seq_flags2 &= ~PENDING_MK_MESSAGE;
			ahd_outb(ahd, SEQ_FLAGS2, seq_flags2);
			mk_msg_scb = NULL;
		}
		if (tid_head != scbid)
			ahd_stitch_tid_list(ahd, tid_prev, tid_head, tid_next);
		if (!SCBID_IS_NULL(tid_head))
			tid_prev = tid_head;
		if (action == SEARCH_PRINT)
			printk(")\n");
	}

	/* Restore saved state. */
	ahd_set_scbptr(ahd, savedscbptr);
	ahd_restore_modes(ahd, saved_modes);
	return (found);
}