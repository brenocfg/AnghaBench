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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t EVP_KDF_size (int /*<<< orphan*/ *) ; 
 size_t SIZE_MAX ; 

__attribute__((used)) static int pkey_kdf_derive(EVP_PKEY_CTX *ctx, unsigned char *key,
                           size_t *keylen)
{
    EVP_KDF_CTX *kctx = ctx->data;
    size_t outlen = EVP_KDF_size(kctx);

    if (outlen == 0 || outlen == SIZE_MAX) {
        /* Variable-output algorithm */
        if (key == NULL)
            return 0;
    } else {
        /* Fixed-output algorithm */
        *keylen = outlen;
        if (key == NULL)
            return 1;
    }
    return EVP_KDF_derive(kctx, key, *keylen);
}