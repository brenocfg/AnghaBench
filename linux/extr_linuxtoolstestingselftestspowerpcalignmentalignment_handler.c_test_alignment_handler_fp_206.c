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
 int /*<<< orphan*/  LOAD_FLOAT_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE_ARCH_2_06 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfiwzx ; 
 int /*<<< orphan*/  printf (char*) ; 

int test_alignment_handler_fp_206(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	printf("Floating point: 2.06\n");

	LOAD_FLOAT_XFORM_TEST(lfiwzx);

	return rc;
}