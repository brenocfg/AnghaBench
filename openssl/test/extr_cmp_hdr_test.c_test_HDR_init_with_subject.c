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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_4__ {int expected; int /*<<< orphan*/  cmp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_HDR_TEST_FIXTURE ; 
 int /*<<< orphan*/  EXECUTE_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set1_subjectName (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SETUP_TEST_FIXTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_ADD (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 int /*<<< orphan*/  execute_HDR_init_test ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  set_up ; 
 int /*<<< orphan*/  tear_down (TYPE_1__*) ; 

__attribute__((used)) static int test_HDR_init_with_subject(void)
{
    SETUP_TEST_FIXTURE(CMP_HDR_TEST_FIXTURE, set_up);
    X509_NAME *subject = NULL;

    fixture->expected = 1;
    if (!TEST_ptr(subject = X509_NAME_new())
        || !TEST_true(X509_NAME_ADD(subject, "CN", "Common Name"))
        || !TEST_true(OSSL_CMP_CTX_set1_subjectName(fixture->cmp_ctx,
                                                    subject))) {
        tear_down(fixture);
        fixture = NULL;
    }
    X509_NAME_free(subject);
    EXECUTE_TEST(execute_HDR_init_test, tear_down);
    return result;
}