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
 int /*<<< orphan*/  PPC_FEATURE2_ARCH_3_00 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 scalar_t__ cacheline_buf ; 
 int /*<<< orphan*/  copy_first (scalar_t__) ; 
 int /*<<< orphan*/  have_hwcap2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_signal_handler () ; 

int test_copy_first_unaligned(void)
{
	/* Only run this test on a P9 or later */
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_00));

	/* Register our signal handler with SIGBUS */
	setup_signal_handler();

	/* +1 makes buf unaligned */
	copy_first(cacheline_buf+1);

	/* We should not get here */
	return 1;
}