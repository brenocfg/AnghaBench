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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  GUEST_SYNC (scalar_t__) ; 
 int /*<<< orphan*/  MSR_IA32_TSC_ADJUST ; 
 scalar_t__ rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_ia32_tsc_adjust(int64_t max)
{
	int64_t adjust;

	adjust = rdmsr(MSR_IA32_TSC_ADJUST);
	GUEST_SYNC(adjust);
	GUEST_ASSERT(adjust <= max);
}