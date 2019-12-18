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
 scalar_t__ one_in_chance (int) ; 

__attribute__((used)) static void mess_with_tm(void)
{
	/* Starts a transaction 33% of the time */
	if (one_in_chance(3)) {
		asm ("tbegin.	;"
		     "beq 8	;");

		/* And suspended half of them */
		if (one_in_chance(2))
			asm("tsuspend.	;");
	}

	/* Call 'tend' in 5% of the runs */
	if (one_in_chance(20))
		asm("tend.	;");
}