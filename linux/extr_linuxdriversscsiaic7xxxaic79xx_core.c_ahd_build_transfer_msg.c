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
typedef  scalar_t__ u_int ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int features; } ;
struct TYPE_4__ {scalar_t__ period; scalar_t__ offset; scalar_t__ ppr_options; scalar_t__ width; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ offset; scalar_t__ period; } ;
struct ahd_initiator_tinfo {TYPE_2__ goal; TYPE_1__ curr; } ;
struct ahd_devinfo {int /*<<< orphan*/  role; int /*<<< orphan*/  target; int /*<<< orphan*/  our_scsiid; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int AHD_WIDE ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_TARGET ; 
 int /*<<< orphan*/  ahd_construct_ppr (struct ahd_softc*,struct ahd_devinfo*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_construct_sdtr (struct ahd_softc*,struct ahd_devinfo*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_construct_wdtr (struct ahd_softc*,struct ahd_devinfo*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_devlimited_syncrate (struct ahd_softc*,struct ahd_initiator_tinfo*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_print_devinfo (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_validate_offset (struct ahd_softc*,struct ahd_initiator_tinfo*,scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void
ahd_build_transfer_msg(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	/*
	 * We need to initiate transfer negotiations.
	 * If our current and goal settings are identical,
	 * we want to renegotiate due to a check condition.
	 */
	struct	ahd_initiator_tinfo *tinfo;
	struct	ahd_tmode_tstate *tstate;
	int	dowide;
	int	dosync;
	int	doppr;
	u_int	period;
	u_int	ppr_options;
	u_int	offset;

	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/*
	 * Filter our period based on the current connection.
	 * If we can't perform DT transfers on this segment (not in LVD
	 * mode for instance), then our decision to issue a PPR message
	 * may change.
	 */
	period = tinfo->goal.period;
	offset = tinfo->goal.offset;
	ppr_options = tinfo->goal.ppr_options;
	/* Target initiated PPR is not allowed in the SCSI spec */
	if (devinfo->role == ROLE_TARGET)
		ppr_options = 0;
	ahd_devlimited_syncrate(ahd, tinfo, &period,
				&ppr_options, devinfo->role);
	dowide = tinfo->curr.width != tinfo->goal.width;
	dosync = tinfo->curr.offset != offset || tinfo->curr.period != period;
	/*
	 * Only use PPR if we have options that need it, even if the device
	 * claims to support it.  There might be an expander in the way
	 * that doesn't.
	 */
	doppr = ppr_options != 0;

	if (!dowide && !dosync && !doppr) {
		dowide = tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT;
		dosync = tinfo->goal.offset != 0;
	}

	if (!dowide && !dosync && !doppr) {
		/*
		 * Force async with a WDTR message if we have a wide bus,
		 * or just issue an SDTR with a 0 offset.
		 */
		if ((ahd->features & AHD_WIDE) != 0)
			dowide = 1;
		else
			dosync = 1;

		if (bootverbose) {
			ahd_print_devinfo(ahd, devinfo);
			printk("Ensuring async\n");
		}
	}
	/* Target initiated PPR is not allowed in the SCSI spec */
	if (devinfo->role == ROLE_TARGET)
		doppr = 0;

	/*
	 * Both the PPR message and SDTR message require the
	 * goal syncrate to be limited to what the target device
	 * is capable of handling (based on whether an LVD->SE
	 * expander is on the bus), so combine these two cases.
	 * Regardless, guarantee that if we are using WDTR and SDTR
	 * messages that WDTR comes first.
	 */
	if (doppr || (dosync && !dowide)) {

		offset = tinfo->goal.offset;
		ahd_validate_offset(ahd, tinfo, period, &offset,
				    doppr ? tinfo->goal.width
					  : tinfo->curr.width,
				    devinfo->role);
		if (doppr) {
			ahd_construct_ppr(ahd, devinfo, period, offset,
					  tinfo->goal.width, ppr_options);
		} else {
			ahd_construct_sdtr(ahd, devinfo, period, offset);
		}
	} else {
		ahd_construct_wdtr(ahd, devinfo, tinfo->goal.width);
	}
}