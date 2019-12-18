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
 int /*<<< orphan*/  LOAD_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE_ARCH_2_06 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbrx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdbrx ; 

int test_alignment_handler_integer_206(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	printf("Integer: 2.06\n");

	LOAD_XFORM_TEST(ldbrx);
	STORE_XFORM_TEST(stdbrx);

	return rc;
}