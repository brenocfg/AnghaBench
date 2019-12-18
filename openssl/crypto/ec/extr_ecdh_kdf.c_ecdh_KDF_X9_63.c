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
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_X963KDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int ecdh_KDF_X9_63(unsigned char *out, size_t outlen,
                   const unsigned char *Z, size_t Zlen,
                   const unsigned char *sinfo, size_t sinfolen,
                   const EVP_MD *md)
{
    int ret = 0;
    EVP_KDF_CTX *kctx = NULL;
    OSSL_PARAM params[4], *p = params;
    const char *mdname = EVP_MD_name(md);
    EVP_KDF *kdf = EVP_KDF_fetch(NULL, OSSL_KDF_NAME_X963KDF, NULL);

    if ((kctx = EVP_KDF_CTX_new(kdf)) != NULL) {
        *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                                (char *)mdname,
                                                strlen(mdname) + 1);
        *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY,
                                                 (void *)Z, Zlen);
        *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_INFO,
                                                 (void *)sinfo, sinfolen);
        *p = OSSL_PARAM_construct_end();

        ret = EVP_KDF_CTX_set_params(kctx, params) > 0
            && EVP_KDF_derive(kctx, out, outlen) > 0;
        EVP_KDF_CTX_free(kctx);
    }
    EVP_KDF_free(kdf);
    return ret;
}