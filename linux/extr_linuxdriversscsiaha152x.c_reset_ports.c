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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRSTCNTRL ; 
 int CH1 ; 
 int CLRCH1 ; 
 int CLRSTCNT ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  DMACNTRL1 ; 
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 int FRERR ; 
 int FWERR ; 
 int RSTFIFO ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISIG ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETRATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 int /*<<< orphan*/  SSTAT4 ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 int /*<<< orphan*/  SXFRCTL1 ; 
 int SYNCERR ; 
 int /*<<< orphan*/  setup_expected_interrupts (struct Scsi_Host*) ; 

__attribute__((used)) static void reset_ports(struct Scsi_Host *shpnt)
{
	unsigned long flags;

	/* disable interrupts */
	SETPORT(DMACNTRL0, RSTFIFO);

	SETPORT(SCSISEQ, 0);

	SETPORT(SXFRCTL1, 0);
	SETPORT(SCSISIG, 0);
	SETRATE(0);

	/* clear all interrupt conditions */
	SETPORT(SSTAT0, 0x7f);
	SETPORT(SSTAT1, 0xef);

	SETPORT(SSTAT4, SYNCERR | FWERR | FRERR);

	SETPORT(DMACNTRL0, 0);
	SETPORT(DMACNTRL1, 0);

	SETPORT(BRSTCNTRL, 0xf1);

	/* clear SCSI fifos and transfer count */
	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	DO_LOCK(flags);
	setup_expected_interrupts(shpnt);
	DO_UNLOCK(flags);
}