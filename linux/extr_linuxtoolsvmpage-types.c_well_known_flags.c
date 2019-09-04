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
typedef  int uint64_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int BITS_COMPOUND ; 
 int /*<<< orphan*/  HUGE ; 
 int KPF_HACKERS_BITS ; 

__attribute__((used)) static uint64_t well_known_flags(uint64_t flags)
{
	/* hide flags intended only for kernel hacker */
	flags &= ~KPF_HACKERS_BITS;

	/* hide non-hugeTLB compound pages */
	if ((flags & BITS_COMPOUND) && !(flags & BIT(HUGE)))
		flags &= ~BITS_COMPOUND;

	return flags;
}