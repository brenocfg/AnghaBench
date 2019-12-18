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
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_FLOAT_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_FLOAT_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  lfd ; 
 int /*<<< orphan*/  lfdu ; 
 int /*<<< orphan*/  lfdux ; 
 int /*<<< orphan*/  lfdx ; 
 int /*<<< orphan*/  lfs ; 
 int /*<<< orphan*/  lfsu ; 
 int /*<<< orphan*/  lfsux ; 
 int /*<<< orphan*/  lfsx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stfd ; 
 int /*<<< orphan*/  stfdu ; 
 int /*<<< orphan*/  stfdux ; 
 int /*<<< orphan*/  stfdx ; 
 int /*<<< orphan*/  stfiwx ; 
 int /*<<< orphan*/  stfs ; 
 int /*<<< orphan*/  stfsu ; 
 int /*<<< orphan*/  stfsux ; 
 int /*<<< orphan*/  stfsx ; 

int test_alignment_handler_fp(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());

	printf("Floating point\n");
	LOAD_FLOAT_DFORM_TEST(lfd);
	LOAD_FLOAT_XFORM_TEST(lfdx);
	LOAD_FLOAT_DFORM_TEST(lfdu);
	LOAD_FLOAT_XFORM_TEST(lfdux);
	LOAD_FLOAT_DFORM_TEST(lfs);
	LOAD_FLOAT_XFORM_TEST(lfsx);
	LOAD_FLOAT_DFORM_TEST(lfsu);
	LOAD_FLOAT_XFORM_TEST(lfsux);
	STORE_FLOAT_DFORM_TEST(stfd);
	STORE_FLOAT_XFORM_TEST(stfdx);
	STORE_FLOAT_DFORM_TEST(stfdu);
	STORE_FLOAT_XFORM_TEST(stfdux);
	STORE_FLOAT_DFORM_TEST(stfs);
	STORE_FLOAT_XFORM_TEST(stfsx);
	STORE_FLOAT_DFORM_TEST(stfsu);
	STORE_FLOAT_XFORM_TEST(stfsux);
	STORE_FLOAT_XFORM_TEST(stfiwx);

	return rc;
}