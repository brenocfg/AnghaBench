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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** shadow_plb ; 

void mkbnd_shadow(uint8_t *ptr, int index, long offset)
{
	uint64_t *lower = (uint64_t *)&(shadow_plb[index][0]);
	uint64_t *upper = (uint64_t *)&(shadow_plb[index][1]);
	*lower = (unsigned long)ptr;
	*upper = (unsigned long)ptr + offset - 1;
}