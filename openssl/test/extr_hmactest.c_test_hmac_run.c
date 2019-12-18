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
struct TYPE_2__ {int key_len; int /*<<< orphan*/  digest; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/ * key; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_get_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 char* pt (unsigned char*,unsigned int) ; 
 TYPE_1__* test ; 

__attribute__((used)) static int test_hmac_run(void)
{
    char *p;
    HMAC_CTX *ctx = NULL;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;
    int ret = 0;

    ctx = HMAC_CTX_new();
    HMAC_CTX_reset(ctx);

    if (!TEST_ptr(ctx)
        || !TEST_ptr_null(HMAC_CTX_get_md(ctx))
        || !TEST_false(HMAC_Init_ex(ctx, NULL, 0, NULL, NULL))
        || !TEST_false(HMAC_Update(ctx, test[4].data, test[4].data_len))
        || !TEST_false(HMAC_Init_ex(ctx, test[4].key, -1, EVP_sha1(), NULL)))
        goto err;

    if (!TEST_true(HMAC_Init_ex(ctx, test[4].key, test[4].key_len, EVP_sha1(), NULL))
        || !TEST_true(HMAC_Update(ctx, test[4].data, test[4].data_len))
        || !TEST_true(HMAC_Final(ctx, buf, &len)))
        goto err;

    p = pt(buf, len);
    if (!TEST_str_eq(p, test[4].digest))
        goto err;

    if (!TEST_false(HMAC_Init_ex(ctx, NULL, 0, EVP_sha256(), NULL)))
        goto err;

    if (!TEST_true(HMAC_Init_ex(ctx, test[5].key, test[5].key_len, EVP_sha256(), NULL))
        || !TEST_ptr_eq(HMAC_CTX_get_md(ctx), EVP_sha256())
        || !TEST_true(HMAC_Update(ctx, test[5].data, test[5].data_len))
        || !TEST_true(HMAC_Final(ctx, buf, &len)))
        goto err;

    p = pt(buf, len);
    if (!TEST_str_eq(p, test[5].digest))
        goto err;

    if (!TEST_true(HMAC_Init_ex(ctx, test[6].key, test[6].key_len, NULL, NULL))
        || !TEST_true(HMAC_Update(ctx, test[6].data, test[6].data_len))
        || !TEST_true(HMAC_Final(ctx, buf, &len)))
        goto err;
    p = pt(buf, len);
    if (!TEST_str_eq(p, test[6].digest))
        goto err;

    ret = 1;
err:
    HMAC_CTX_free(ctx);
    return ret;
}