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
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 scalar_t__ NESTED_TEST_MEM1 ; 
 scalar_t__ NESTED_TEST_MEM2 ; 
 int /*<<< orphan*/  vmcall () ; 

__attribute__((used)) static void l2_guest_code(void)
{
	*(volatile uint64_t *)NESTED_TEST_MEM1;
	*(volatile uint64_t *)NESTED_TEST_MEM1 = 1;
	GUEST_SYNC(true);
	GUEST_SYNC(false);

	*(volatile uint64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(true);
	*(volatile uint64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(true);
	GUEST_SYNC(false);

	/* Exit to L1 and never come back.  */
	vmcall();
}