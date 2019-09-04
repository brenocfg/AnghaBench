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
typedef  int u_int ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int flags; int features; int /*<<< orphan*/  our_id; } ;
struct ahd_initiator_tinfo {int dummy; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_NEG_ALWAYS ; 
 int AHD_RESET_BUS_A ; 
 int AHD_WIDE ; 
 int /*<<< orphan*/  AIC79XX_RESET_DELAY ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,char,int /*<<< orphan*/ ,int,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_freeze_simq (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahd_release_simq (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_reset_channel (struct ahd_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 scalar_t__ aic79xx_no_reset ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_linux_initialize_scsi_bus(struct ahd_softc *ahd)
{
	u_int target_id;
	u_int numtarg;
	unsigned long s;

	target_id = 0;
	numtarg = 0;

	if (aic79xx_no_reset != 0)
		ahd->flags &= ~AHD_RESET_BUS_A;

	if ((ahd->flags & AHD_RESET_BUS_A) != 0)
		ahd_reset_channel(ahd, 'A', /*initiate_reset*/TRUE);
	else
		numtarg = (ahd->features & AHD_WIDE) ? 16 : 8;

	ahd_lock(ahd, &s);

	/*
	 * Force negotiation to async for all targets that
	 * will not see an initial bus reset.
	 */
	for (; target_id < numtarg; target_id++) {
		struct ahd_devinfo devinfo;
		struct ahd_initiator_tinfo *tinfo;
		struct ahd_tmode_tstate *tstate;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    target_id, &tstate);
		ahd_compile_devinfo(&devinfo, ahd->our_id, target_id,
				    CAM_LUN_WILDCARD, 'A', ROLE_INITIATOR);
		ahd_update_neg_request(ahd, &devinfo, tstate,
				       tinfo, AHD_NEG_ALWAYS);
	}
	ahd_unlock(ahd, &s);
	/* Give the bus some time to recover */
	if ((ahd->flags & AHD_RESET_BUS_A) != 0) {
		ahd_freeze_simq(ahd);
		msleep(AIC79XX_RESET_DELAY);
		ahd_release_simq(ahd);
	}
}