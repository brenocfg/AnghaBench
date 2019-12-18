#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; int /*<<< orphan*/  data_size; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,char const*) ; 
 scalar_t__ TEST_ptr (char const*) ; 
 scalar_t__ TEST_size_t_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_str_eq (char const*,char const*) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* greeting_request ; 
 int /*<<< orphan*/  ossl_provider_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_provider_get_params (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int test_provider(OSSL_PROVIDER *prov, const char *expected_greeting)
{
    const char *greeting = NULL;
    int ret = 0;

    ret =
        TEST_true(ossl_provider_activate(prov))
        && TEST_true(ossl_provider_get_params(prov, greeting_request))
        && TEST_ptr(greeting = greeting_request[0].data)
        && TEST_size_t_gt(greeting_request[0].data_size, 0)
        && TEST_str_eq(greeting, expected_greeting);

    TEST_info("Got this greeting: %s\n", greeting);
    ossl_provider_free(prov);
    return ret;
}