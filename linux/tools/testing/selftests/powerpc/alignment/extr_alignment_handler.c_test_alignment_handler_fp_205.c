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
 int /*<<< orphan*/  LOAD_FLOAT_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD_FLOAT_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE_ARCH_2_05 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_FLOAT_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_FLOAT_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfdp ; 
 int /*<<< orphan*/  lfdpx ; 
 int /*<<< orphan*/  lfiwax ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stfdp ; 
 int /*<<< orphan*/  stfdpx ; 

int test_alignment_handler_fp_205(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_05));

	printf("Floating point: 2.05\n");

	LOAD_FLOAT_DFORM_TEST(lfdp);
	LOAD_FLOAT_XFORM_TEST(lfdpx);
	LOAD_FLOAT_XFORM_TEST(lfiwax);
	STORE_FLOAT_DFORM_TEST(stfdp);
	STORE_FLOAT_XFORM_TEST(stfdpx);

	return rc;
}