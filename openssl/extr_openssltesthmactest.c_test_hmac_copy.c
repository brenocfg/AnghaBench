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
struct TYPE_2__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  HMAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 char* pt (unsigned char*,unsigned int) ; 
 TYPE_1__* test ; 

__attribute__((used)) static int test_hmac_copy(void)
{
    char *p;
    HMAC_CTX *ctx = NULL, *ctx2 = NULL;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;
    int ret = 0;

    ctx = HMAC_CTX_new();
    ctx2 = HMAC_CTX_new();
    if (!TEST_ptr(ctx) || !TEST_ptr(ctx2))
        goto err;

    if (!TEST_true(HMAC_Init_ex(ctx, test[7].key, test[7].key_len, EVP_sha1(), NULL))
        || !TEST_true(HMAC_Update(ctx, test[7].data, test[7].data_len))
        || !TEST_true(HMAC_CTX_copy(ctx2, ctx))
        || !TEST_true(HMAC_Final(ctx2, buf, &len)))
        goto err;

    p = pt(buf, len);
    if (!TEST_str_eq(p, test[7].digest))
        goto err;

    ret = 1;
err:
    HMAC_CTX_free(ctx2);
    HMAC_CTX_free(ctx);
    return ret;
}