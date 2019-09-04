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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_PKEY_CTX_add1_tls1_prf_seed (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set1_tls1_prf_secret (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 scalar_t__ EVP_PKEY_CTX_set_tls1_prf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_TLS1_PRF ; 
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS1_PRF ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_prf_md (int /*<<< orphan*/ *) ; 

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
    EVP_PKEY_CTX *pctx = NULL;
    int ret = 0;

    if (md == NULL) {
        /* Should never happen */
        if (fatal)
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_PRF,
                     ERR_R_INTERNAL_ERROR);
        else
            SSLerr(SSL_F_TLS1_PRF, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_TLS1_PRF, NULL);
    if (pctx == NULL || EVP_PKEY_derive_init(pctx) <= 0
        || EVP_PKEY_CTX_set_tls1_prf_md(pctx, md) <= 0
        || EVP_PKEY_CTX_set1_tls1_prf_secret(pctx, sec, (int)slen) <= 0
        || EVP_PKEY_CTX_add1_tls1_prf_seed(pctx, seed1, (int)seed1_len) <= 0
        || EVP_PKEY_CTX_add1_tls1_prf_seed(pctx, seed2, (int)seed2_len) <= 0
        || EVP_PKEY_CTX_add1_tls1_prf_seed(pctx, seed3, (int)seed3_len) <= 0
        || EVP_PKEY_CTX_add1_tls1_prf_seed(pctx, seed4, (int)seed4_len) <= 0
        || EVP_PKEY_CTX_add1_tls1_prf_seed(pctx, seed5, (int)seed5_len) <= 0
        || EVP_PKEY_derive(pctx, out, &olen) <= 0) {
        if (fatal)
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_PRF,
                     ERR_R_INTERNAL_ERROR);
        else
            SSLerr(SSL_F_TLS1_PRF, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ret = 1;

 err:
    EVP_PKEY_CTX_free(pctx);
    return ret;
}