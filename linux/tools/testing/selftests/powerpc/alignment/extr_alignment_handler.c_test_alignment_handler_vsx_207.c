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
 int /*<<< orphan*/  PPC_FEATURE2_ARCH_2_07 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_VSX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lxsiwax ; 
 int /*<<< orphan*/  lxsiwzx ; 
 int /*<<< orphan*/  lxsspx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stxsiwx ; 
 int /*<<< orphan*/  stxsspx ; 

int test_alignment_handler_vsx_207(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	printf("VSX: 2.07B\n");
	LOAD_VSX_XFORM_TEST(lxsspx);
	LOAD_VSX_XFORM_TEST(lxsiwax);
	LOAD_VSX_XFORM_TEST(lxsiwzx);
	STORE_VSX_XFORM_TEST(stxsspx);
	STORE_VSX_XFORM_TEST(stxsiwx);
	return rc;
}