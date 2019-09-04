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
 int /*<<< orphan*/  BESCR_PME ; 
 int /*<<< orphan*/  SPRN_BESCRR ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ebb_global_disable(void)
{
	/* Disable EBBs & freeze counters, events are still scheduled */
	mtspr(SPRN_BESCRR, BESCR_PME);
	mb();
}