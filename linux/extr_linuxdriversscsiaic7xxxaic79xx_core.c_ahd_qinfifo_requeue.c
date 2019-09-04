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
struct scb {TYPE_2__* hscb; } ;
struct ahd_softc {TYPE_1__* next_queued_hscb; int /*<<< orphan*/  qinfifonext; int /*<<< orphan*/ * qinfifo; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_hscb_busaddr; int /*<<< orphan*/  hscb_busaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  hscb_busaddr; } ;

/* Variables and functions */
 size_t AHD_QIN_WRAP (int /*<<< orphan*/ ) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  NEXT_QUEUED_SCB_ADDR ; 
 int /*<<< orphan*/  SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  ahd_le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outl (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_sync_scb (struct ahd_softc*,struct scb*,int) ; 

__attribute__((used)) static void
ahd_qinfifo_requeue(struct ahd_softc *ahd, struct scb *prev_scb,
		    struct scb *scb)
{
	if (prev_scb == NULL) {
		uint32_t busaddr;

		busaddr = ahd_le32toh(scb->hscb->hscb_busaddr);
		ahd_outl(ahd, NEXT_QUEUED_SCB_ADDR, busaddr);
	} else {
		prev_scb->hscb->next_hscb_busaddr = scb->hscb->hscb_busaddr;
		ahd_sync_scb(ahd, prev_scb, 
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
	}
	ahd->qinfifo[AHD_QIN_WRAP(ahd->qinfifonext)] = SCB_GET_TAG(scb);
	ahd->qinfifonext++;
	scb->hscb->next_hscb_busaddr = ahd->next_queued_hscb->hscb_busaddr;
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
}