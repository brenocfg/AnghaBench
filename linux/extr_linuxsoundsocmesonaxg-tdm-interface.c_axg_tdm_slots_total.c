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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int AXG_TDM_NUM_LANES ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int axg_tdm_slots_total(u32 *mask)
{
	unsigned int slots = 0;
	int i;

	if (!mask)
		return 0;

	/* Count the total number of slots provided by all 4 lanes */
	for (i = 0; i < AXG_TDM_NUM_LANES; i++)
		slots += hweight32(mask[i]);

	return slots;
}