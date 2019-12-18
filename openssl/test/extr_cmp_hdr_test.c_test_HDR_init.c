#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ref ;
struct TYPE_4__ {int expected; int /*<<< orphan*/  cmp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_HDR_TEST_FIXTURE ; 
 int CMP_TEST_REFVALUE_LENGTH ; 
 int /*<<< orphan*/  EXECUTE_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set1_referenceValue (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  SETUP_TEST_FIXTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_HDR_init_test ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  set_up ; 
 int /*<<< orphan*/  tear_down (TYPE_1__*) ; 

__attribute__((used)) static int test_HDR_init(void)
{
    SETUP_TEST_FIXTURE(CMP_HDR_TEST_FIXTURE, set_up);
    unsigned char ref[CMP_TEST_REFVALUE_LENGTH];

    fixture->expected = 1;
    if (!TEST_int_eq(1, RAND_bytes(ref, sizeof(ref)))
            || !TEST_true(OSSL_CMP_CTX_set1_referenceValue(fixture->cmp_ctx,
                                                           ref, sizeof(ref)))) {
        tear_down(fixture);
        fixture = NULL;
    }
    EXECUTE_TEST(execute_HDR_init_test, tear_down);
    return result;
}