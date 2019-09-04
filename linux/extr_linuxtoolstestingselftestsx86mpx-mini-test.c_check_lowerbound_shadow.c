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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf1 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_lower_brs ; 
 int /*<<< orphan*/ ** shadow_plb ; 

void check_lowerbound_shadow(uint8_t *ptr, int index)
{
	uint64_t *lower = (uint64_t *)&(shadow_plb[index][0]);
	if (*lower > (uint64_t)(unsigned long)ptr)
		num_lower_brs++;
	else
		dprintf1("LowerBoundChk passed:%p\n", ptr);
}