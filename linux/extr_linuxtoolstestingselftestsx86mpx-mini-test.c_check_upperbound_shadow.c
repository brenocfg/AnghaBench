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
 int /*<<< orphan*/  num_upper_brs ; 
 int /*<<< orphan*/ ** shadow_plb ; 

void check_upperbound_shadow(uint8_t *ptr, int index)
{
	uint64_t upper = *(uint64_t *)&(shadow_plb[index][1]);
	if (upper < (uint64_t)(unsigned long)ptr)
		num_upper_brs++;
	else
		dprintf1("UpperBoundChk passed:%p\n", ptr);
}