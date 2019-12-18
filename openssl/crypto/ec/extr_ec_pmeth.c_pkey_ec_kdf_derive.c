#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kdf_type; size_t kdf_outlen; int /*<<< orphan*/  kdf_md; int /*<<< orphan*/  kdf_ukmlen; int /*<<< orphan*/  kdf_ukm; } ;
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ EC_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_PKEY_EC_KDF_DERIVE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_PKEY_ECDH_KDF_NONE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  ecdh_KDF_X9_63 (unsigned char*,size_t,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pkey_ec_derive (TYPE_1__*,unsigned char*,size_t*) ; 

__attribute__((used)) static int pkey_ec_kdf_derive(EVP_PKEY_CTX *ctx,
                              unsigned char *key, size_t *keylen)
{
    EC_PKEY_CTX *dctx = ctx->data;
    unsigned char *ktmp = NULL;
    size_t ktmplen;
    int rv = 0;
    if (dctx->kdf_type == EVP_PKEY_ECDH_KDF_NONE)
        return pkey_ec_derive(ctx, key, keylen);
    if (!key) {
        *keylen = dctx->kdf_outlen;
        return 1;
    }
    if (*keylen != dctx->kdf_outlen)
        return 0;
    if (!pkey_ec_derive(ctx, NULL, &ktmplen))
        return 0;
    if ((ktmp = OPENSSL_malloc(ktmplen)) == NULL) {
        ECerr(EC_F_PKEY_EC_KDF_DERIVE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (!pkey_ec_derive(ctx, ktmp, &ktmplen))
        goto err;
    /* Do KDF stuff */
    if (!ecdh_KDF_X9_63(key, *keylen, ktmp, ktmplen,
                        dctx->kdf_ukm, dctx->kdf_ukmlen, dctx->kdf_md))
        goto err;
    rv = 1;

 err:
    OPENSSL_clear_free(ktmp, ktmplen);
    return rv;
}