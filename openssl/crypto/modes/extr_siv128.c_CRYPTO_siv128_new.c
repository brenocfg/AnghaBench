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
typedef  int /*<<< orphan*/  SIV128_CONTEXT ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int CRYPTO_siv128_init (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 

SIV128_CONTEXT *CRYPTO_siv128_new(const unsigned char *key, int klen, EVP_CIPHER* cbc, EVP_CIPHER* ctr)
{
    SIV128_CONTEXT *ctx;
    int ret;

    if ((ctx = OPENSSL_malloc(sizeof(*ctx))) != NULL) {
        ret = CRYPTO_siv128_init(ctx, key, klen, cbc, ctr);
        if (ret)
            return ctx;
        OPENSSL_free(ctx);
    }

    return NULL;
}