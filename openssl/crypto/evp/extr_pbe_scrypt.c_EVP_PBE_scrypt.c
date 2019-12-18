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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PBE_SCRYPT ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 int EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_R_PARAMETER_TOO_LARGE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_SCRYPT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PASSWORD ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_MAXMEM ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_N ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_P ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_R ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 void* OSSL_PARAM_construct_uint64 (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ SCRYPT_MAX_MEM ; 
 scalar_t__ UINT32_MAX ; 

int EVP_PBE_scrypt(const char *pass, size_t passlen,
                   const unsigned char *salt, size_t saltlen,
                   uint64_t N, uint64_t r, uint64_t p, uint64_t maxmem,
                   unsigned char *key, size_t keylen)
{
    const char *empty = "";
    int rv = 1;
    EVP_KDF *kdf;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[7], *z = params;

    if (r > UINT32_MAX || p > UINT32_MAX) {
        EVPerr(EVP_F_EVP_PBE_SCRYPT, EVP_R_PARAMETER_TOO_LARGE);
        return 0;
    }

    /* Maintain existing behaviour. */
    if (pass == NULL) {
        pass = empty;
        passlen = 0;
    }
    if (salt == NULL) {
        salt = (const unsigned char *)empty;
        saltlen = 0;
    }
    if (maxmem == 0)
        maxmem = SCRYPT_MAX_MEM;

    kdf = EVP_KDF_fetch(NULL, OSSL_KDF_NAME_SCRYPT, NULL);
    kctx = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kctx == NULL)
        return 0;

    *z++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_PASSWORD,
                                              (unsigned char *)pass,
                                                      passlen);
    *z++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT,
                                             (unsigned char *)salt, saltlen);
    *z++ = OSSL_PARAM_construct_uint64(OSSL_KDF_PARAM_SCRYPT_N, &N);
    *z++ = OSSL_PARAM_construct_uint64(OSSL_KDF_PARAM_SCRYPT_R, &r);
    *z++ = OSSL_PARAM_construct_uint64(OSSL_KDF_PARAM_SCRYPT_P, &p);
    *z++ = OSSL_PARAM_construct_uint64(OSSL_KDF_PARAM_SCRYPT_MAXMEM, &maxmem);
    *z = OSSL_PARAM_construct_end();
    if (EVP_KDF_CTX_set_params(kctx, params) != 1
            || EVP_KDF_derive(kctx, key, keylen) != 1)
        rv = 0;

    EVP_KDF_CTX_free(kctx);
    return rv;
}