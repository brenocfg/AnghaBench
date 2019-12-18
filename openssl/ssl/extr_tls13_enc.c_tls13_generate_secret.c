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
typedef  int /*<<< orphan*/  derived_secret_label ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_HKDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MODE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_int (int /*<<< orphan*/ ,int*) ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_GENERATE_SECRET ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* default_zeros ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,unsigned char*,int,unsigned char*,size_t,unsigned char*,size_t,int) ; 

int tls13_generate_secret(SSL *s, const EVP_MD *md,
                          const unsigned char *prevsecret,
                          const unsigned char *insecret,
                          size_t insecretlen,
                          unsigned char *outsecret)
{
    size_t mdlen, prevsecretlen;
    int mdleni;
    int ret;
    EVP_KDF *kdf;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[5], *p = params;
    int mode = EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY;
    const char *mdname = EVP_MD_name(md);
#ifdef CHARSET_EBCDIC
    static const char derived_secret_label[] = { 0x64, 0x65, 0x72, 0x69, 0x76, 0x65, 0x64, 0x00 };
#else
    static const char derived_secret_label[] = "derived";
#endif
    unsigned char preextractsec[EVP_MAX_MD_SIZE];

    kdf = EVP_KDF_fetch(NULL, OSSL_KDF_NAME_HKDF, NULL);
    kctx = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    mdleni = EVP_MD_size(md);
    /* Ensure cast to size_t is safe */
    if (!ossl_assert(mdleni >= 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);
        EVP_KDF_CTX_free(kctx);
        return 0;
    }
    mdlen = (size_t)mdleni;

    if (insecret == NULL) {
        insecret = default_zeros;
        insecretlen = mdlen;
    }
    if (prevsecret == NULL) {
        prevsecret = default_zeros;
        prevsecretlen = 0;
    } else {
        EVP_MD_CTX *mctx = EVP_MD_CTX_new();
        unsigned char hash[EVP_MAX_MD_SIZE];

        /* The pre-extract derive step uses a hash of no messages */
        if (mctx == NULL
                || EVP_DigestInit_ex(mctx, md, NULL) <= 0
                || EVP_DigestFinal_ex(mctx, hash, NULL) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                     ERR_R_INTERNAL_ERROR);
            EVP_MD_CTX_free(mctx);
            EVP_KDF_CTX_free(kctx);
            return 0;
        }
        EVP_MD_CTX_free(mctx);

        /* Generate the pre-extract secret */
        if (!tls13_hkdf_expand(s, md, prevsecret,
                               (unsigned char *)derived_secret_label,
                               sizeof(derived_secret_label) - 1, hash, mdlen,
                               preextractsec, mdlen, 1)) {
            /* SSLfatal() already called */
            EVP_KDF_CTX_free(kctx);
            return 0;
        }

        prevsecret = preextractsec;
        prevsecretlen = mdlen;
    }

    *p++ = OSSL_PARAM_construct_int(OSSL_KDF_PARAM_MODE, &mode);
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                            (char *)mdname, strlen(mdname) + 1);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY,
                                             (unsigned char *)insecret,
                                             insecretlen);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT,
                                             (unsigned char *)prevsecret,
                                             prevsecretlen);
    *p++ = OSSL_PARAM_construct_end();

    ret = EVP_KDF_CTX_set_params(kctx, params) <= 0
        || EVP_KDF_derive(kctx, outsecret, mdlen) <= 0;

    if (ret != 0)
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);

    EVP_KDF_CTX_free(kctx);
    if (prevsecret == preextractsec)
        OPENSSL_cleanse(preextractsec, mdlen);
    return ret == 0;
}