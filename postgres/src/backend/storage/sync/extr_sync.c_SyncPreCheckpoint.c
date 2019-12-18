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
 int /*<<< orphan*/  checkpoint_cycle_ctr ; 

void
SyncPreCheckpoint(void)
{
	/*
	 * Any unlink requests arriving after this point will be assigned the next
	 * cycle counter, and won't be unlinked until next checkpoint.
	 */
	checkpoint_cycle_ctr++;
}