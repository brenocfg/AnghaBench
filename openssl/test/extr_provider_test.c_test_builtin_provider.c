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
 int /*<<< orphan*/  OSSL_PROVIDER_add_builtin (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROVIDER_INIT_FUNCTION_NAME ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 scalar_t__ test_provider (char const*) ; 

__attribute__((used)) static int test_builtin_provider(void)
{
    const char *name = "p_test_builtin";

    return
        TEST_true(OSSL_PROVIDER_add_builtin(NULL, name,
                                            PROVIDER_INIT_FUNCTION_NAME))
        && test_provider(name);
}