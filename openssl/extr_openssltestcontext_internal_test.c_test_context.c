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
struct TYPE_4__ {int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ FOO ;

/* Variables and functions */
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  foo_method ; 
 TYPE_1__* openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_context(OPENSSL_CTX *ctx)
{
    FOO *data = NULL;

    return TEST_ptr(data = openssl_ctx_get_data(ctx, 0, &foo_method))
        /* OPENSSL_zalloc in foo_new() initialized it to zero */
        && TEST_int_eq(data->i, 42);
}