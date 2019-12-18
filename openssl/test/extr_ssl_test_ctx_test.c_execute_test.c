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
struct TYPE_3__ {int /*<<< orphan*/  expected_ctx; int /*<<< orphan*/  test_section; } ;
typedef  TYPE_1__ SSL_TEST_CTX_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  SSL_TEST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_TEST_CTX_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_TEST_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  testctx_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_test(SSL_TEST_CTX_TEST_FIXTURE *fixture)
{
    int success = 0;
    SSL_TEST_CTX *ctx;

    if (!TEST_ptr(ctx = SSL_TEST_CTX_create(conf, fixture->test_section))
            || !testctx_eq(ctx, fixture->expected_ctx))
        goto err;

    success = 1;
 err:
    SSL_TEST_CTX_free(ctx);
    return success;
}