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
struct ahc_softc {int features; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_ALL_INTERRUPTS ; 
 int AHC_REMOVABLE ; 
 int ENSELO ; 
 int FALSE ; 
 int /*<<< orphan*/  INTSTAT ; 
 int INT_PEND ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int SELDO ; 
 int SELINGO ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int TRUE ; 
 int /*<<< orphan*/  ahc_clear_critical_section (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_delay (int) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_intr (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_platform_flushwork (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

void
ahc_pause_and_flushwork(struct ahc_softc *ahc)
{
	int intstat;
	int maxloops;
	int paused;

	maxloops = 1000;
	ahc->flags |= AHC_ALL_INTERRUPTS;
	paused = FALSE;
	do {
		if (paused) {
			ahc_unpause(ahc);
			/*
			 * Give the sequencer some time to service
			 * any active selections.
			 */
			ahc_delay(500);
		}
		ahc_intr(ahc);
		ahc_pause(ahc);
		paused = TRUE;
		ahc_outb(ahc, SCSISEQ, ahc_inb(ahc, SCSISEQ) & ~ENSELO);
		intstat = ahc_inb(ahc, INTSTAT);
		if ((intstat & INT_PEND) == 0) {
			ahc_clear_critical_section(ahc);
			intstat = ahc_inb(ahc, INTSTAT);
		}
	} while (--maxloops
	      && (intstat != 0xFF || (ahc->features & AHC_REMOVABLE) == 0)
	      && ((intstat & INT_PEND) != 0
	       || (ahc_inb(ahc, SSTAT0) & (SELDO|SELINGO)) != 0));
	if (maxloops == 0) {
		printk("Infinite interrupt loop, INTSTAT = %x",
		       ahc_inb(ahc, INTSTAT));
	}
	ahc_platform_flushwork(ahc);
	ahc->flags &= ~AHC_ALL_INTERRUPTS;
}