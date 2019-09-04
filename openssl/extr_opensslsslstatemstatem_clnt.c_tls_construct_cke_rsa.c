#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_9__ {unsigned char* pms; size_t pmslen; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_11__ {int client_version; scalar_t__ version; TYPE_3__ s3; TYPE_1__* session; } ;
struct TYPE_8__ {int /*<<< orphan*/ * peer; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_encrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,size_t) ; 
 scalar_t__ EVP_PKEY_encrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_RSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 scalar_t__ SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CKE_RSA ; 
 size_t SSL_MAX_MASTER_KEY_LENGTH ; 
 int /*<<< orphan*/  SSL_R_BAD_RSA_ENCRYPT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_log_rsa_client_key_exchange (TYPE_4__*,unsigned char*,size_t,unsigned char*,size_t) ; 

__attribute__((used)) static int tls_construct_cke_rsa(SSL *s, WPACKET *pkt)
{
#ifndef OPENSSL_NO_RSA
    unsigned char *encdata = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *pctx = NULL;
    size_t enclen;
    unsigned char *pms = NULL;
    size_t pmslen = 0;

    if (s->session->peer == NULL) {
        /*
         * We should always have a server certificate with SSL_kRSA.
         */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    pkey = X509_get0_pubkey(s->session->peer);
    if (EVP_PKEY_get0_RSA(pkey) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    pmslen = SSL_MAX_MASTER_KEY_LENGTH;
    pms = OPENSSL_malloc(pmslen);
    if (pms == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    pms[0] = s->client_version >> 8;
    pms[1] = s->client_version & 0xff;
    /* TODO(size_t): Convert this function */
    if (RAND_bytes(pms + 2, (int)(pmslen - 2)) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Fix buf for TLS and beyond */
    if (s->version > SSL3_VERSION && !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    pctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (pctx == NULL || EVP_PKEY_encrypt_init(pctx) <= 0
        || EVP_PKEY_encrypt(pctx, NULL, &enclen, pms, pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_EVP_LIB);
        goto err;
    }
    if (!WPACKET_allocate_bytes(pkt, enclen, &encdata)
            || EVP_PKEY_encrypt(pctx, encdata, &enclen, pms, pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 SSL_R_BAD_RSA_ENCRYPT);
        goto err;
    }
    EVP_PKEY_CTX_free(pctx);
    pctx = NULL;

    /* Fix buf for TLS and beyond */
    if (s->version > SSL3_VERSION && !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    /* Log the premaster secret, if logging is enabled. */
    if (!ssl_log_rsa_client_key_exchange(s, encdata, enclen, pms, pmslen)) {
        /* SSLfatal() already called */
        goto err;
    }

    s->s3.tmp.pms = pms;
    s->s3.tmp.pmslen = pmslen;

    return 1;
 err:
    OPENSSL_clear_free(pms, pmslen);
    EVP_PKEY_CTX_free(pctx);

    return 0;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_RSA,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}