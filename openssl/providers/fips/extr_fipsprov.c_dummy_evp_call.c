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
typedef  int /*<<< orphan*/  randbuf ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  exptd ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_KDF ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ANY ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rand_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/ * OPENSSL_CTX_get0_public_drbg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_PBKDF2 ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (void*) ; 
 scalar_t__ RAND_DRBG_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int SHA256_DIGEST_LENGTH ; 
 scalar_t__ memcmp (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int dummy_evp_call(void *provctx)
{
    OPENSSL_CTX *libctx = PROV_LIBRARY_CONTEXT_OF(provctx);
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_MD *sha256 = EVP_MD_fetch(libctx, "SHA256", NULL);
    EVP_KDF *kdf = EVP_KDF_fetch(libctx, OSSL_KDF_NAME_PBKDF2, NULL);
    char msg[] = "Hello World!";
    const unsigned char exptd[] = {
        0x7f, 0x83, 0xb1, 0x65, 0x7f, 0xf1, 0xfc, 0x53, 0xb9, 0x2d, 0xc1, 0x81,
        0x48, 0xa1, 0xd6, 0x5d, 0xfc, 0x2d, 0x4b, 0x1f, 0xa3, 0xd6, 0x77, 0x28,
        0x4a, 0xdd, 0xd2, 0x00, 0x12, 0x6d, 0x90, 0x69
    };
    unsigned int dgstlen = 0;
    unsigned char dgst[SHA256_DIGEST_LENGTH];
    int ret = 0;
    BN_CTX *bnctx = NULL;
    BIGNUM *a = NULL, *b = NULL;
    unsigned char randbuf[128];
    RAND_DRBG *drbg = OPENSSL_CTX_get0_public_drbg(libctx);
#ifndef OPENSSL_NO_EC
    EC_KEY *key = NULL;
#endif

    if (ctx == NULL || sha256 == NULL || drbg == NULL || kdf == NULL)
        goto err;

    if (!EVP_DigestInit_ex(ctx, sha256, NULL))
        goto err;
    if (!EVP_DigestUpdate(ctx, msg, sizeof(msg) - 1))
        goto err;
    if (!EVP_DigestFinal(ctx, dgst, &dgstlen))
        goto err;
    if (dgstlen != sizeof(exptd) || memcmp(dgst, exptd, sizeof(exptd)) != 0)
        goto err;

    bnctx = BN_CTX_new_ex(libctx);
    if (bnctx == NULL)
        goto err;
    BN_CTX_start(bnctx);
    a = BN_CTX_get(bnctx);
    b = BN_CTX_get(bnctx);
    if (b == NULL)
        goto err;
    BN_zero(a);
    if (!BN_one(b)
        || !BN_add(a, a, b)
        || BN_cmp(a, b) != 0)
        goto err;

    if (RAND_DRBG_bytes(drbg, randbuf, sizeof(randbuf)) <= 0)
        goto err;

    if (!BN_rand_ex(a, 256, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY, bnctx))
        goto err;

#ifndef OPENSSL_NO_EC
    /* Do some dummy EC calls */
    key = EC_KEY_new_by_curve_name_ex(libctx, NID_X9_62_prime256v1);
    if (key == NULL)
        goto err;

    if (!EC_KEY_generate_key(key))
        goto err;
#endif

    ret = 1;
 err:
    BN_CTX_end(bnctx);
    BN_CTX_free(bnctx);

    EVP_KDF_free(kdf);
    EVP_MD_CTX_free(ctx);
    EVP_MD_free(sha256);

#ifndef OPENSSL_NO_EC
    EC_KEY_free(key);
#endif
    return ret;
}