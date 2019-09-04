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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_SYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guest_code(void)
{
	uint64_t msr_platform_info;

	for (;;) {
		msr_platform_info = rdmsr(MSR_PLATFORM_INFO);
		GUEST_SYNC(msr_platform_info);
		asm volatile ("inc %r11");
	}
}