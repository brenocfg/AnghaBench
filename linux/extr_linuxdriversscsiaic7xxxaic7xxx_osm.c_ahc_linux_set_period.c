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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {scalar_t__ channel; int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_syncrate {int dummy; } ;
struct ahc_softc {int dummy; } ;
struct TYPE_4__ {unsigned int ppr_options; unsigned long offset; } ;
struct ahc_initiator_tinfo {TYPE_2__ goal; } ;
struct ahc_devinfo {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  this_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_SYNCRATE_DT ; 
 int /*<<< orphan*/  AHC_TRANS_GOAL ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned long MAX_OFFSET ; 
 unsigned int MSG_EXT_PPR_DT_REQ ; 
 unsigned int MSG_EXT_PPR_QAS_REQ ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahc_tmode_tstate**) ; 
 struct ahc_syncrate* ahc_find_syncrate (struct ahc_softc*,int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahc_set_syncrate (struct ahc_softc*,struct ahc_devinfo*,struct ahc_syncrate const*,int,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,unsigned long*) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_max_width (struct scsi_target*) ; 
 scalar_t__ spi_width (struct scsi_target*) ; 

__attribute__((used)) static void ahc_linux_set_period(struct scsi_target *starget, int period)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct ahc_softc *ahc = *((struct ahc_softc **)shost->hostdata);
	struct ahc_tmode_tstate *tstate;
	struct ahc_initiator_tinfo *tinfo 
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	struct ahc_devinfo devinfo;
	unsigned int ppr_options = tinfo->goal.ppr_options;
	unsigned long flags;
	unsigned long offset = tinfo->goal.offset;
	const struct ahc_syncrate *syncrate;

	if (offset == 0)
		offset = MAX_OFFSET;

	if (period < 9)
		period = 9;	/* 12.5ns is our minimum */
	if (period == 9) {
		if (spi_max_width(starget))
			ppr_options |= MSG_EXT_PPR_DT_REQ;
		else
			/* need wide for DT and need DT for 12.5 ns */
			period = 10;
	}

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);

	/* all PPR requests apart from QAS require wide transfers */
	if (ppr_options & ~MSG_EXT_PPR_QAS_REQ) {
		if (spi_width(starget) == 0)
			ppr_options &= MSG_EXT_PPR_QAS_REQ;
	}

	syncrate = ahc_find_syncrate(ahc, &period, &ppr_options, AHC_SYNCRATE_DT);
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
}