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

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int catch_sigill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event ; 
 int event_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pmc1 ; 

__attribute__((used)) static int child(void)
{
	/* Even though we have EBE=0 we can still see the EBB regs */
	FAIL_IF(mfspr(SPRN_BESCR) != 0);
	FAIL_IF(mfspr(SPRN_EBBHR) != 0);
	FAIL_IF(mfspr(SPRN_EBBRR) != 0);

	FAIL_IF(catch_sigill(write_pmc1));

	/* We can still read from the event, though it is on our parent */
	FAIL_IF(event_read(&event));

	return 0;
}