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
 unsigned int LVL_GRAN (unsigned int) ; 
 unsigned int LVL_MASK ; 
 int LVL_OFFS (unsigned int) ; 
 unsigned int LVL_SHIFT (unsigned int) ; 

__attribute__((used)) static inline unsigned calc_index(unsigned expires, unsigned lvl)
{
	expires = (expires + LVL_GRAN(lvl)) >> LVL_SHIFT(lvl);
	return LVL_OFFS(lvl) + (expires & LVL_MASK);
}