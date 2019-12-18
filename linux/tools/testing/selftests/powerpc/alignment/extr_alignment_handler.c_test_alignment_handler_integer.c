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
 int /*<<< orphan*/  LOAD_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  STORE_DFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_XFORM_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_open_fb0 () ; 
 int /*<<< orphan*/  lbz ; 
 int /*<<< orphan*/  lbzu ; 
 int /*<<< orphan*/  lbzux ; 
 int /*<<< orphan*/  lbzx ; 
 int /*<<< orphan*/  ld ; 
 int /*<<< orphan*/  ldu ; 
 int /*<<< orphan*/  ldux ; 
 int /*<<< orphan*/  ldx ; 
 int /*<<< orphan*/  lha ; 
 int /*<<< orphan*/  lhau ; 
 int /*<<< orphan*/  lhaux ; 
 int /*<<< orphan*/  lhax ; 
 int /*<<< orphan*/  lhbrx ; 
 int /*<<< orphan*/  lhz ; 
 int /*<<< orphan*/  lhzu ; 
 int /*<<< orphan*/  lhzux ; 
 int /*<<< orphan*/  lhzx ; 
 int /*<<< orphan*/  lmw ; 
 int /*<<< orphan*/  lwa ; 
 int /*<<< orphan*/  lwaux ; 
 int /*<<< orphan*/  lwax ; 
 int /*<<< orphan*/  lwbrx ; 
 int /*<<< orphan*/  lwz ; 
 int /*<<< orphan*/  lwzu ; 
 int /*<<< orphan*/  lwzux ; 
 int /*<<< orphan*/  lwzx ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stb ; 
 int /*<<< orphan*/  stbu ; 
 int /*<<< orphan*/  stbux ; 
 int /*<<< orphan*/  stbx ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  stdu ; 
 int /*<<< orphan*/  stdux ; 
 int /*<<< orphan*/  stdx ; 
 int /*<<< orphan*/  sth ; 
 int /*<<< orphan*/  sthbrx ; 
 int /*<<< orphan*/  sthu ; 
 int /*<<< orphan*/  sthux ; 
 int /*<<< orphan*/  sthx ; 
 int /*<<< orphan*/  stmw ; 
 int /*<<< orphan*/  stw ; 
 int /*<<< orphan*/  stwbrx ; 
 int /*<<< orphan*/  stwu ; 
 int /*<<< orphan*/  stwux ; 
 int /*<<< orphan*/  stwx ; 

int test_alignment_handler_integer(void)
{
	int rc = 0;

	SKIP_IF(!can_open_fb0());

	printf("Integer\n");
	LOAD_DFORM_TEST(lbz);
	LOAD_DFORM_TEST(lbzu);
	LOAD_XFORM_TEST(lbzx);
	LOAD_XFORM_TEST(lbzux);
	LOAD_DFORM_TEST(lhz);
	LOAD_DFORM_TEST(lhzu);
	LOAD_XFORM_TEST(lhzx);
	LOAD_XFORM_TEST(lhzux);
	LOAD_DFORM_TEST(lha);
	LOAD_DFORM_TEST(lhau);
	LOAD_XFORM_TEST(lhax);
	LOAD_XFORM_TEST(lhaux);
	LOAD_XFORM_TEST(lhbrx);
	LOAD_DFORM_TEST(lwz);
	LOAD_DFORM_TEST(lwzu);
	LOAD_XFORM_TEST(lwzx);
	LOAD_XFORM_TEST(lwzux);
	LOAD_DFORM_TEST(lwa);
	LOAD_XFORM_TEST(lwax);
	LOAD_XFORM_TEST(lwaux);
	LOAD_XFORM_TEST(lwbrx);
	LOAD_DFORM_TEST(ld);
	LOAD_DFORM_TEST(ldu);
	LOAD_XFORM_TEST(ldx);
	LOAD_XFORM_TEST(ldux);
	LOAD_DFORM_TEST(lmw);
	STORE_DFORM_TEST(stb);
	STORE_XFORM_TEST(stbx);
	STORE_DFORM_TEST(stbu);
	STORE_XFORM_TEST(stbux);
	STORE_DFORM_TEST(sth);
	STORE_XFORM_TEST(sthx);
	STORE_DFORM_TEST(sthu);
	STORE_XFORM_TEST(sthux);
	STORE_XFORM_TEST(sthbrx);
	STORE_DFORM_TEST(stw);
	STORE_XFORM_TEST(stwx);
	STORE_DFORM_TEST(stwu);
	STORE_XFORM_TEST(stwux);
	STORE_XFORM_TEST(stwbrx);
	STORE_DFORM_TEST(std);
	STORE_XFORM_TEST(stdx);
	STORE_DFORM_TEST(stdu);
	STORE_XFORM_TEST(stdux);
	STORE_DFORM_TEST(stmw);

	return rc;
}