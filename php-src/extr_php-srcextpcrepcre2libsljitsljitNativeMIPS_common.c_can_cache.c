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
typedef  int sljit_sw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int OFFS_REG_MASK ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 int SLJIT_MEM ; 

__attribute__((used)) static sljit_s32 can_cache(sljit_s32 arg, sljit_sw argw, sljit_s32 next_arg, sljit_sw next_argw)
{
	SLJIT_ASSERT((arg & SLJIT_MEM) && (next_arg & SLJIT_MEM));

	/* Simple operation except for updates. */
	if (arg & OFFS_REG_MASK) {
		argw &= 0x3;
		next_argw &= 0x3;
		if (argw && argw == next_argw && (arg == next_arg || (arg & OFFS_REG_MASK) == (next_arg & OFFS_REG_MASK)))
			return 1;
		return 0;
	}

	if (arg == next_arg) {
		if (((next_argw - argw) <= SIMM_MAX && (next_argw - argw) >= SIMM_MIN))
			return 1;
		return 0;
	}

	return 0;
}