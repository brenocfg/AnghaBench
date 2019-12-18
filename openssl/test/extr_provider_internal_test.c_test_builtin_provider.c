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
 int /*<<< orphan*/  PROVIDER_INIT_FUNCTION_NAME ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expected_greeting1 (char const*) ; 
 int /*<<< orphan*/ * ossl_provider_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_builtin_provider(void)
{
    const char *name = "p_test_builtin";
    OSSL_PROVIDER *prov = NULL;

    return
        TEST_ptr(prov =
                 ossl_provider_new(NULL, name, PROVIDER_INIT_FUNCTION_NAME, 0))
        && test_provider(prov, expected_greeting1(name));
}