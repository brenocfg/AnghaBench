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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_CTX_new () ; 
 int /*<<< orphan*/ * OSSL_PROVIDER_load (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 char* test_get_argument (size_t) ; 
 size_t test_get_argument_count () ; 

__attribute__((used)) static int load_providers(OPENSSL_CTX **libctx, OSSL_PROVIDER *prov[])
{
    OPENSSL_CTX *ctx;
    int ret = 0;
    size_t i;

    ctx = OPENSSL_CTX_new();
    if (!TEST_ptr(ctx))
        goto err;

    if (test_get_argument_count() > 2)
        goto err;

    for (i = 0; i < test_get_argument_count(); ++i) {
        char *provname = test_get_argument(i);
        prov[i] = OSSL_PROVIDER_load(ctx, provname);
        if (!TEST_ptr(prov[i]))
            goto err;
    }
    ret = 1;
    *libctx = ctx;
err:
    return ret;
}