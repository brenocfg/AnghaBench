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
 int /*<<< orphan*/  LOAD_VSX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE_ARCH_2_06 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_VSX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lxsdx ; 
 int /*<<< orphan*/  lxvd2x ; 
 int /*<<< orphan*/  lxvdsx ; 
 int /*<<< orphan*/  lxvw4x ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stxsdx ; 
 int /*<<< orphan*/  stxvd2x ; 
 int /*<<< orphan*/  stxvw4x ; 

int test_alignment_handler_vsx_206(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	printf("VSX: 2.06B\n");
	LOAD_VSX_XFORM_TEST(lxvd2x);
	LOAD_VSX_XFORM_TEST(lxvw4x);
	LOAD_VSX_XFORM_TEST(lxsdx);
	LOAD_VSX_XFORM_TEST(lxvdsx);
	STORE_VSX_XFORM_TEST(stxvd2x);
	STORE_VSX_XFORM_TEST(stxvw4x);
	STORE_VSX_XFORM_TEST(stxsdx);
	return rc;
}