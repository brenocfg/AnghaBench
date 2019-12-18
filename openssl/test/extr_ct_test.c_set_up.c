#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* test_case_name; unsigned long long epoch_time_in_ms; struct TYPE_9__* ctlog_store; } ;
typedef  TYPE_1__ CT_TEST_FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/  CTLOG_STORE_free (TYPE_1__*) ; 
 int /*<<< orphan*/  CTLOG_STORE_load_default_file (TYPE_1__*) ; 
 TYPE_1__* CTLOG_STORE_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static CT_TEST_FIXTURE *set_up(const char *const test_case_name)
{
    CT_TEST_FIXTURE *fixture = NULL;

    if (!TEST_ptr(fixture = OPENSSL_zalloc(sizeof(*fixture))))
        goto end;
    fixture->test_case_name = test_case_name;
    fixture->epoch_time_in_ms = 1473269626000ULL; /* Sep 7 17:33:46 2016 GMT */
    if (!TEST_ptr(fixture->ctlog_store = CTLOG_STORE_new())
            || !TEST_int_eq(
                    CTLOG_STORE_load_default_file(fixture->ctlog_store), 1))
        goto end;
    return fixture;

end:
    if (fixture != NULL)
        CTLOG_STORE_free(fixture->ctlog_store);
    OPENSSL_free(fixture);
    TEST_error("Failed to setup");
    return NULL;
}