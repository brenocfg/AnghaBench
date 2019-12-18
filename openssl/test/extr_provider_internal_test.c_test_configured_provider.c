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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;

/* Variables and functions */
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_provider (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int test_configured_provider(void)
{
    const char *name = "p_test_configured";
    OSSL_PROVIDER *prov = NULL;
    /* This MUST match the config file */
    const char *expected_greeting =
        "Hello OpenSSL, greetings from Test Provider";

    return
        TEST_ptr(prov = ossl_provider_find(NULL, name, 0))
        && test_provider(prov, expected_greeting);
}