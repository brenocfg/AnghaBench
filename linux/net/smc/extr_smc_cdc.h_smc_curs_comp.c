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
union smc_host_cursor {scalar_t__ wrap; scalar_t__ count; } ;

/* Variables and functions */
 int smc_curs_diff (unsigned int,union smc_host_cursor*,union smc_host_cursor*) ; 

__attribute__((used)) static inline int smc_curs_comp(unsigned int size,
				union smc_host_cursor *old,
				union smc_host_cursor *new)
{
	if (old->wrap > new->wrap ||
	    (old->wrap == new->wrap && old->count > new->count))
		return -smc_curs_diff(size, new, old);
	return smc_curs_diff(size, old, new);
}