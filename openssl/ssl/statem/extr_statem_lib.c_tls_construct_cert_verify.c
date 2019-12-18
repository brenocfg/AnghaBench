#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_18__ {int sig; int /*<<< orphan*/  sigalg; } ;
struct TYPE_14__ {TYPE_1__* cert; TYPE_6__* sigalg; } ;
struct TYPE_15__ {TYPE_2__ tmp; } ;
struct TYPE_17__ {scalar_t__ version; TYPE_4__* session; TYPE_3__ s3; } ;
struct TYPE_16__ {int /*<<< orphan*/  master_key; scalar_t__ master_key_length; } ;
struct TYPE_13__ {int /*<<< orphan*/ * privatekey; } ;
typedef  TYPE_5__ SSL ;
typedef  TYPE_6__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_reverse (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_CTRL_SSL3_MASTER_SECRET ; 
 scalar_t__ EVP_DigestSign (int /*<<< orphan*/ *,unsigned char*,size_t*,void*,size_t) ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,void*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 scalar_t__ EVP_MD_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_RSA_PSS ; 
 size_t EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int NID_id_GostR3410_2001 ; 
 int NID_id_GostR3410_2012_256 ; 
 int NID_id_GostR3410_2012_512 ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_SALTLEN_DIGEST ; 
 scalar_t__ SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CERT_VERIFY ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_5__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS13_TBS_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  get_cert_verify_tbs_data (TYPE_5__*,unsigned char*,void**,size_t*) ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls1_lookup_md (TYPE_6__ const*,int /*<<< orphan*/  const**) ; 

int tls_construct_cert_verify(SSL *s, WPACKET *pkt)
{
    EVP_PKEY *pkey = NULL;
    const EVP_MD *md = NULL;
    EVP_MD_CTX *mctx = NULL;
    EVP_PKEY_CTX *pctx = NULL;
    size_t hdatalen = 0, siglen = 0;
    void *hdata;
    unsigned char *sig = NULL;
    unsigned char tls13tbs[TLS13_TBS_PREAMBLE_SIZE + EVP_MAX_MD_SIZE];
    const SIGALG_LOOKUP *lu = s->s3.tmp.sigalg;

    if (lu == NULL || s->s3.tmp.cert == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    pkey = s->s3.tmp.cert->privatekey;

    if (pkey == NULL || !tls1_lookup_md(lu, &md)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    mctx = EVP_MD_CTX_new();
    if (mctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Get the data to be signed */
    if (!get_cert_verify_tbs_data(s, tls13tbs, &hdata, &hdatalen)) {
        /* SSLfatal() already called */
        goto err;
    }

    if (SSL_USE_SIGALGS(s) && !WPACKET_put_bytes_u16(pkt, lu->sigalg)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    siglen = EVP_PKEY_size(pkey);
    sig = OPENSSL_malloc(siglen);
    if (sig == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_DigestSignInit(mctx, &pctx, md, NULL, pkey) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_EVP_LIB);
        goto err;
    }

    if (lu->sig == EVP_PKEY_RSA_PSS) {
        if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) <= 0
            || EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx,
                                                RSA_PSS_SALTLEN_DIGEST) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                     ERR_R_EVP_LIB);
            goto err;
        }
    }
    if (s->version == SSL3_VERSION) {
        if (EVP_DigestSignUpdate(mctx, hdata, hdatalen) <= 0
            /*
             * TODO(3.0) Replace this when EVP_MD_CTX_ctrl() is deprecated
             * with a call to ssl3_digest_master_key_set_params()
             */
            || EVP_MD_CTX_ctrl(mctx, EVP_CTRL_SSL3_MASTER_SECRET,
                               (int)s->session->master_key_length,
                               s->session->master_key) <= 0
            || EVP_DigestSignFinal(mctx, sig, &siglen) <= 0) {

            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                     ERR_R_EVP_LIB);
            goto err;
        }
    } else if (EVP_DigestSign(mctx, sig, &siglen, hdata, hdatalen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_EVP_LIB);
        goto err;
    }

#ifndef OPENSSL_NO_GOST
    {
        int pktype = lu->sig;

        if (pktype == NID_id_GostR3410_2001
            || pktype == NID_id_GostR3410_2012_256
            || pktype == NID_id_GostR3410_2012_512)
            BUF_reverse(sig, NULL, siglen);
    }
#endif

    if (!WPACKET_sub_memcpy_u16(pkt, sig, siglen)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    /* Digest cached records and discard handshake buffer */
    if (!ssl3_digest_cached_records(s, 0)) {
        /* SSLfatal() already called */
        goto err;
    }

    OPENSSL_free(sig);
    EVP_MD_CTX_free(mctx);
    return 1;
 err:
    OPENSSL_free(sig);
    EVP_MD_CTX_free(mctx);
    return 0;
}