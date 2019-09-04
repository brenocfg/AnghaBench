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
struct ahd_softc {int dummy; } ;
struct TYPE_2__ {int errno; int /*<<< orphan*/  errmesg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CHANNELS ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_NO_HBA ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  ahd_abort_scbs (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_free (struct ahd_softc*) ; 
 TYPE_1__* ahd_hard_errors ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int num_errors ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_handle_hwerrint(struct ahd_softc *ahd)
{
	/*
	 * Some catastrophic hardware error has occurred.
	 * Print it for the user and disable the controller.
	 */
	int i;
	int error;

	error = ahd_inb(ahd, ERROR);
	for (i = 0; i < num_errors; i++) {
		if ((error & ahd_hard_errors[i].errno) != 0)
			printk("%s: hwerrint, %s\n",
			       ahd_name(ahd), ahd_hard_errors[i].errmesg);
	}

	ahd_dump_card_state(ahd);
	panic("BRKADRINT");

	/* Tell everyone that this HBA is no longer available */
	ahd_abort_scbs(ahd, CAM_TARGET_WILDCARD, ALL_CHANNELS,
		       CAM_LUN_WILDCARD, SCB_LIST_NULL, ROLE_UNKNOWN,
		       CAM_NO_HBA);

	/* Tell the system that this controller has gone away. */
	ahd_free(ahd);
}