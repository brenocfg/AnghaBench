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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_TLS1_PRF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SECRET ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SEED ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS1_PRF ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_prf_md (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int tls1_PRF(SSL *s,
                    const void *seed1, size_t seed1_len,
                    const void *seed2, size_t seed2_len,
                    const void *seed3, size_t seed3_len,
                    const void *seed4, size_t seed4_len,
                    const void *seed5, size_t seed5_len,
                    const unsigned char *sec, size_t slen,
                    unsigned char *out, size_t olen, int fatal)
{
    const EVP_MD *md = ssl_prf_md(s);
    EVP_KDF *kdf;
    EVP_KDF_CTX *kctx = NULL;
    OSSL_PARAM params[8], *p = params;
    const char *mdname;

    if (md == NULL) {
        /* Should never happen */
        if (fatal)
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_PRF,
                     ERR_R_INTERNAL_ERROR);
        else
            SSLerr(SSL_F_TLS1_PRF, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    kdf = EVP_KDF_fetch(NULL, OSSL_KDF_NAME_TLS1_PRF, NULL);
    if (kdf == NULL)
        goto err;
    kctx = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kctx == NULL)
        goto err;
    mdname = EVP_MD_name(md);
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                            (char *)mdname, strlen(mdname) + 1);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SECRET,
                                             (unsigned char *)sec,
                                             (size_t)slen);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SEED,
                                             (void *)seed1, (size_t)seed1_len);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SEED,
                                             (void *)seed2, (size_t)seed2_len);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SEED,
                                             (void *)seed3, (size_t)seed3_len);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SEED,
                                             (void *)seed4, (size_t)seed4_len);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SEED,
                                             (void *)seed5, (size_t)seed5_len);
    *p = OSSL_PARAM_construct_end();
    if (EVP_KDF_CTX_set_params(kctx, params)
            && EVP_KDF_derive(kctx, out, olen)) {
        EVP_KDF_CTX_free(kctx);
        return 1;
    }

 err:
    if (fatal)
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_PRF,
                 ERR_R_INTERNAL_ERROR);
    else
        SSLerr(SSL_F_TLS1_PRF, ERR_R_INTERNAL_ERROR);
    EVP_KDF_CTX_free(kctx);
    return 0;
}