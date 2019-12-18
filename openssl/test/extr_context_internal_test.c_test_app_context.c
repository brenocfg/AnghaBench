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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_CTX_new () ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ test_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_app_context(void)
{
    OPENSSL_CTX *ctx = NULL;
    int result =
        TEST_ptr(ctx = OPENSSL_CTX_new())
        && test_context(ctx);

    OPENSSL_CTX_free(ctx);
    return result;
}