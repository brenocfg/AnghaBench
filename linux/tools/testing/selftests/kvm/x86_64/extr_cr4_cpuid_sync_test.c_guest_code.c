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
 int /*<<< orphan*/  GUEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUEST_DONE () ; 
 int /*<<< orphan*/  GUEST_SYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86_CR4_OSXSAVE ; 
 int /*<<< orphan*/  cr4_cpuid_is_sync () ; 
 int /*<<< orphan*/  get_cr4 () ; 
 int /*<<< orphan*/  set_cr4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guest_code(void)
{
	uint64_t cr4;

	/* turn on CR4.OSXSAVE */
	cr4 = get_cr4();
	cr4 |= X86_CR4_OSXSAVE;
	set_cr4(cr4);

	/* verify CR4.OSXSAVE == CPUID.OSXSAVE */
	GUEST_ASSERT(cr4_cpuid_is_sync());

	/* notify hypervisor to change CR4 */
	GUEST_SYNC(0);

	/* check again */
	GUEST_ASSERT(cr4_cpuid_is_sync());

	GUEST_DONE();
}