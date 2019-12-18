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
 int /*<<< orphan*/  LOAD_VMX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_FEATURE_HAS_ALTIVEC ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_VMX_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lvx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stvebx ; 
 int /*<<< orphan*/  stvehx ; 
 int /*<<< orphan*/  stvewx ; 
 int /*<<< orphan*/  stvx ; 
 int /*<<< orphan*/  stvxl ; 

int test_alignment_handler_vmx(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());
	SKIP_IF(!have_hwcap(PPC_FEATURE_HAS_ALTIVEC));

	printf("VMX\n");
	LOAD_VMX_XFORM_TEST(lvx);

	/*
	 * FIXME: These loads only load part of the register, so our
	 * testing method doesn't work. Also they don't take alignment
	 * faults, so it's kinda pointless anyway
	 *
	 LOAD_VMX_XFORM_TEST(lvebx)
	 LOAD_VMX_XFORM_TEST(lvehx)
	 LOAD_VMX_XFORM_TEST(lvewx)
	 LOAD_VMX_XFORM_TEST(lvxl)
	*/
	STORE_VMX_XFORM_TEST(stvx);
	STORE_VMX_XFORM_TEST(stvebx);
	STORE_VMX_XFORM_TEST(stvehx);
	STORE_VMX_XFORM_TEST(stvewx);
	STORE_VMX_XFORM_TEST(stvxl);
	return rc;
}