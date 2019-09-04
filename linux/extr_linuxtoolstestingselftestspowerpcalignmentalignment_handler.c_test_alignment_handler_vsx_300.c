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
 int /*<<< orphan*/  LOAD_VMX_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD_VSX_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD_VSX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE2_ARCH_3_00 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_VMX_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_VSX_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_VSX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lxsd ; 
 int /*<<< orphan*/  lxsibzx ; 
 int /*<<< orphan*/  lxsihzx ; 
 int /*<<< orphan*/  lxssp ; 
 int /*<<< orphan*/  lxv ; 
 int /*<<< orphan*/  lxvb16x ; 
 int /*<<< orphan*/  lxvh8x ; 
 int /*<<< orphan*/  lxvl ; 
 int /*<<< orphan*/  lxvll ; 
 int /*<<< orphan*/  lxvwsx ; 
 int /*<<< orphan*/  lxvx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stxsd ; 
 int /*<<< orphan*/  stxsibx ; 
 int /*<<< orphan*/  stxsihx ; 
 int /*<<< orphan*/  stxssp ; 
 int /*<<< orphan*/  stxv ; 
 int /*<<< orphan*/  stxvb16x ; 
 int /*<<< orphan*/  stxvh8x ; 
 int /*<<< orphan*/  stxvl ; 
 int /*<<< orphan*/  stxvll ; 
 int /*<<< orphan*/  stxvx ; 

int test_alignment_handler_vsx_300(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_00));
	printf("VSX: 3.00B\n");
	LOAD_VMX_DFORM_TEST(lxsd);
	LOAD_VSX_XFORM_TEST(lxsibzx);
	LOAD_VSX_XFORM_TEST(lxsihzx);
	LOAD_VMX_DFORM_TEST(lxssp);
	LOAD_VSX_DFORM_TEST(lxv);
	LOAD_VSX_XFORM_TEST(lxvb16x);
	LOAD_VSX_XFORM_TEST(lxvh8x);
	LOAD_VSX_XFORM_TEST(lxvx);
	LOAD_VSX_XFORM_TEST(lxvwsx);
	LOAD_VSX_XFORM_TEST(lxvl);
	LOAD_VSX_XFORM_TEST(lxvll);
	STORE_VMX_DFORM_TEST(stxsd);
	STORE_VSX_XFORM_TEST(stxsibx);
	STORE_VSX_XFORM_TEST(stxsihx);
	STORE_VMX_DFORM_TEST(stxssp);
	STORE_VSX_DFORM_TEST(stxv);
	STORE_VSX_XFORM_TEST(stxvb16x);
	STORE_VSX_XFORM_TEST(stxvh8x);
	STORE_VSX_XFORM_TEST(stxvx);
	STORE_VSX_XFORM_TEST(stxvl);
	STORE_VSX_XFORM_TEST(stxvll);
	return rc;
}