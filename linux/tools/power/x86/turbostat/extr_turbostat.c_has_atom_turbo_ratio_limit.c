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
 scalar_t__ has_slv_msrs (unsigned int,unsigned int) ; 

int has_atom_turbo_ratio_limit(unsigned int family, unsigned int model)
{
	if (has_slv_msrs(family, model))
		return 1;

	return 0;
}