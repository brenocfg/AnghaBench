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
typedef  int u8 ;
struct scsi_ctrl_blk {int tastat; size_t target; int mode; int flags; int senselen; int buflen; int ident; int cdblen; int* cdb; int /*<<< orphan*/  (* post ) (int*,int*) ;int /*<<< orphan*/  hastat; scalar_t__ tagmsg; int /*<<< orphan*/  senseptr; int /*<<< orphan*/  bufptr; } ;
struct initio_host {scalar_t__ active; scalar_t__ addr; scalar_t__* act_tags; scalar_t__* max_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_BAD_PHAS ; 
 int INI_QUEUE_FULL ; 
 int SCF_DIR ; 
 int SCF_DONE ; 
 int SCF_POST ; 
 int SCF_SENSE ; 
 int SCF_SG ; 
 int SCM_RSENS ; 
 int SCSICMD_RequestSense ; 
 int TSS_INT_PENDING ; 
 scalar_t__ TUL_SStatus0 ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_append_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 struct scsi_ctrl_blk* initio_find_done_scb (struct initio_host*) ; 
 int /*<<< orphan*/ * initio_find_first_pend_scb (struct initio_host*) ; 
 int /*<<< orphan*/  initio_push_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 
 int /*<<< orphan*/  tulip_scsi (struct initio_host*) ; 

__attribute__((used)) static int tulip_main(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;

	for (;;) {
		tulip_scsi(host);	/* Call tulip_scsi              */

		/* Walk the list of completed SCBs */
		while ((scb = initio_find_done_scb(host)) != NULL) {	/* find done entry */
			if (scb->tastat == INI_QUEUE_FULL) {
				host->max_tags[scb->target] =
				    host->act_tags[scb->target] - 1;
				scb->tastat = 0;
				initio_append_pend_scb(host, scb);
				continue;
			}
			if (!(scb->mode & SCM_RSENS)) {		/* not in auto req. sense mode */
				if (scb->tastat == 2) {

					/* clr sync. nego flag */

					if (scb->flags & SCF_SENSE) {
						u8 len;
						len = scb->senselen;
						if (len == 0)
							len = 1;
						scb->buflen = scb->senselen;
						scb->bufptr = scb->senseptr;
						scb->flags &= ~(SCF_SG | SCF_DIR);	/* for xfer_data_in */
						/* so, we won't report wrong direction in xfer_data_in,
						   and won't report HOST_DO_DU in state_6 */
						scb->mode = SCM_RSENS;
						scb->ident &= 0xBF;	/* Disable Disconnect */
						scb->tagmsg = 0;
						scb->tastat = 0;
						scb->cdblen = 6;
						scb->cdb[0] = SCSICMD_RequestSense;
						scb->cdb[1] = 0;
						scb->cdb[2] = 0;
						scb->cdb[3] = 0;
						scb->cdb[4] = len;
						scb->cdb[5] = 0;
						initio_push_pend_scb(host, scb);
						break;
					}
				}
			} else {	/* in request sense mode */

				if (scb->tastat == 2) {		/* check contition status again after sending
									   requset sense cmd 0x3 */
					scb->hastat = HOST_BAD_PHAS;
				}
				scb->tastat = 2;
			}
			scb->flags |= SCF_DONE;
			if (scb->flags & SCF_POST) {
				/* FIXME: only one post method and lose casts */
				(*scb->post) ((u8 *) host, (u8 *) scb);
			}
		}		/* while */
		/* find_active: */
		if (inb(host->addr + TUL_SStatus0) & TSS_INT_PENDING)
			continue;
		if (host->active)	/* return to OS and wait for xfer_done_ISR/Selected_ISR */
			return 1;	/* return to OS, enable interrupt */
		/* Check pending SCB            */
		if (initio_find_first_pend_scb(host) == NULL)
			return 1;	/* return to OS, enable interrupt */
	}			/* End of for loop */
	/* statement won't reach here */
}