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
struct ahc_softc {int flags; } ;

/* Variables and functions */
 int AHC_PAGESCBS ; 
 int /*<<< orphan*/  FREE_SCBH ; 
 int /*<<< orphan*/  SCBPTR ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_NEXT ; 
 int /*<<< orphan*/  SCB_TAG ; 
 int /*<<< orphan*/  ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_add_curscb_to_free_list(struct ahc_softc *ahc)
{
	/*
	 * Invalidate the tag so that our abort
	 * routines don't think it's active.
	 */
	ahc_outb(ahc, SCB_TAG, SCB_LIST_NULL);

	if ((ahc->flags & AHC_PAGESCBS) != 0) {
		ahc_outb(ahc, SCB_NEXT, ahc_inb(ahc, FREE_SCBH));
		ahc_outb(ahc, FREE_SCBH, ahc_inb(ahc, SCBPTR));
	}
}