#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_get_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ ) ; 
 TYPE_1__* test ; 

__attribute__((used)) static int test_hmac_bad(void)
{
    HMAC_CTX *ctx = NULL;
    int ret = 0;

    ctx = HMAC_CTX_new();
    if (!TEST_ptr(ctx)
        || !TEST_ptr_null(HMAC_CTX_get_md(ctx))
        || !TEST_false(HMAC_Init_ex(ctx, NULL, 0, NULL, NULL))
        || !TEST_false(HMAC_Update(ctx, test[4].data, test[4].data_len))
        || !TEST_false(HMAC_Init_ex(ctx, NULL, 0, EVP_sha1(), NULL))
        || !TEST_false(HMAC_Update(ctx, test[4].data, test[4].data_len)))
        goto err;

    ret = 1;
err:
    HMAC_CTX_free(ctx);
    return ret;
}