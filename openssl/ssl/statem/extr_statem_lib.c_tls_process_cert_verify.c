#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_14__ {int cert_req; int /*<<< orphan*/  peer_sigalg; } ;
struct TYPE_15__ {int /*<<< orphan*/ * handshake_buffer; TYPE_2__ tmp; } ;
struct TYPE_16__ {scalar_t__ version; TYPE_3__ s3; int /*<<< orphan*/  server; TYPE_1__* session; } ;
struct TYPE_13__ {int /*<<< orphan*/  master_key; scalar_t__ master_key_length; int /*<<< orphan*/ * peer; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_reverse (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_CTRL_SSL3_MASTER_SECRET ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,unsigned char const*,unsigned int,void*,size_t) ; 
 scalar_t__ EVP_DigestVerifyFinal (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 scalar_t__ EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,void*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 scalar_t__ EVP_MD_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_PROCESSING ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int NID_id_GostR3410_2001 ; 
 int NID_id_GostR3410_2012_256 ; 
 int NID_id_GostR3410_2012_512 ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned int) ; 
 int /*<<< orphan*/  OSSL_TRACE1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_SALTLEN_DIGEST ; 
 scalar_t__ SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_DECRYPT_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CERT_VERIFY ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_PACKET ; 
 int /*<<< orphan*/  SSL_R_BAD_SIGNATURE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE ; 
 int /*<<< orphan*/  SSL_R_WRONG_SIGNATURE_SIZE ; 
 scalar_t__ SSL_USE_PSS (TYPE_4__*) ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS ; 
 int TLS13_TBS_PREAMBLE_SIZE ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cert_verify_tbs_data (TYPE_4__*,unsigned char*,void**,size_t*) ; 
 int /*<<< orphan*/ * ssl_cert_lookup_by_pkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tls12_check_peer_sigalg (TYPE_4__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_lookup_md (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  tls1_set_peer_legacy_sigalg (TYPE_4__*,int /*<<< orphan*/ *) ; 

MSG_PROCESS_RETURN tls_process_cert_verify(SSL *s, PACKET *pkt)
{
    EVP_PKEY *pkey = NULL;
    const unsigned char *data;
#ifndef OPENSSL_NO_GOST
    unsigned char *gost_data = NULL;
#endif
    MSG_PROCESS_RETURN ret = MSG_PROCESS_ERROR;
    int j;
    unsigned int len;
    X509 *peer;
    const EVP_MD *md = NULL;
    size_t hdatalen = 0;
    void *hdata;
    unsigned char tls13tbs[TLS13_TBS_PREAMBLE_SIZE + EVP_MAX_MD_SIZE];
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX *pctx = NULL;

    if (mctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    peer = s->session->peer;
    pkey = X509_get0_pubkey(peer);
    if (pkey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (ssl_cert_lookup_by_pkey(pkey, NULL) == NULL) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 SSL_R_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE);
        goto err;
    }

    if (SSL_USE_SIGALGS(s)) {
        unsigned int sigalg;

        if (!PACKET_get_net_2(pkt, &sigalg)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     SSL_R_BAD_PACKET);
            goto err;
        }
        if (tls12_check_peer_sigalg(s, sigalg, pkey) <= 0) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (!tls1_set_peer_legacy_sigalg(s, pkey)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     ERR_R_INTERNAL_ERROR);
            goto err;
    }

    if (!tls1_lookup_md(s->s3.tmp.peer_sigalg, &md)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (SSL_USE_SIGALGS(s))
        OSSL_TRACE1(TLS, "USING TLSv1.2 HASH %s\n",
                    md == NULL ? "n/a" : EVP_MD_name(md));

    /* Check for broken implementations of GOST ciphersuites */
    /*
     * If key is GOST and len is exactly 64 or 128, it is signature without
     * length field (CryptoPro implementations at least till TLS 1.2)
     */
#ifndef OPENSSL_NO_GOST
    if (!SSL_USE_SIGALGS(s)
        && ((PACKET_remaining(pkt) == 64
             && (EVP_PKEY_id(pkey) == NID_id_GostR3410_2001
                 || EVP_PKEY_id(pkey) == NID_id_GostR3410_2012_256))
            || (PACKET_remaining(pkt) == 128
                && EVP_PKEY_id(pkey) == NID_id_GostR3410_2012_512))) {
        len = PACKET_remaining(pkt);
    } else
#endif
    if (!PACKET_get_net_2(pkt, &len)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 SSL_R_LENGTH_MISMATCH);
        goto err;
    }

    j = EVP_PKEY_size(pkey);
    if (((int)len > j) || ((int)PACKET_remaining(pkt) > j)
        || (PACKET_remaining(pkt) == 0)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 SSL_R_WRONG_SIGNATURE_SIZE);
        goto err;
    }
    if (!PACKET_get_bytes(pkt, &data, len)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 SSL_R_LENGTH_MISMATCH);
        goto err;
    }

    if (!get_cert_verify_tbs_data(s, tls13tbs, &hdata, &hdatalen)) {
        /* SSLfatal() already called */
        goto err;
    }

    OSSL_TRACE1(TLS, "Using client verify alg %s\n",
                md == NULL ? "n/a" : EVP_MD_name(md));

    if (EVP_DigestVerifyInit(mctx, &pctx, md, NULL, pkey) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                 ERR_R_EVP_LIB);
        goto err;
    }
#ifndef OPENSSL_NO_GOST
    {
        int pktype = EVP_PKEY_id(pkey);
        if (pktype == NID_id_GostR3410_2001
            || pktype == NID_id_GostR3410_2012_256
            || pktype == NID_id_GostR3410_2012_512) {
            if ((gost_data = OPENSSL_malloc(len)) == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_PROCESS_CERT_VERIFY, ERR_R_MALLOC_FAILURE);
                goto err;
            }
            BUF_reverse(gost_data, data, len);
            data = gost_data;
        }
    }
#endif

    if (SSL_USE_PSS(s)) {
        if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) <= 0
            || EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx,
                                                RSA_PSS_SALTLEN_DIGEST) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     ERR_R_EVP_LIB);
            goto err;
        }
    }
    if (s->version == SSL3_VERSION) {
        /*
         * TODO(3.0) Replace this when EVP_MD_CTX_ctrl() is deprecated
         * with a call to ssl3_digest_master_key_set_params()
         */
        if (EVP_DigestVerifyUpdate(mctx, hdata, hdatalen) <= 0
                || EVP_MD_CTX_ctrl(mctx, EVP_CTRL_SSL3_MASTER_SECRET,
                                   (int)s->session->master_key_length,
                                    s->session->master_key) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     ERR_R_EVP_LIB);
            goto err;
        }
        if (EVP_DigestVerifyFinal(mctx, data, len) <= 0) {
            SSLfatal(s, SSL_AD_DECRYPT_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     SSL_R_BAD_SIGNATURE);
            goto err;
        }
    } else {
        j = EVP_DigestVerify(mctx, data, len, hdata, hdatalen);
        if (j <= 0) {
            SSLfatal(s, SSL_AD_DECRYPT_ERROR, SSL_F_TLS_PROCESS_CERT_VERIFY,
                     SSL_R_BAD_SIGNATURE);
            goto err;
        }
    }

    /*
     * In TLSv1.3 on the client side we make sure we prepare the client
     * certificate after the CertVerify instead of when we get the
     * CertificateRequest. This is because in TLSv1.3 the CertificateRequest
     * comes *before* the Certificate message. In TLSv1.2 it comes after. We
     * want to make sure that SSL_get_peer_certificate() will return the actual
     * server certificate from the client_cert_cb callback.
     */
    if (!s->server && SSL_IS_TLS13(s) && s->s3.tmp.cert_req == 1)
        ret = MSG_PROCESS_CONTINUE_PROCESSING;
    else
        ret = MSG_PROCESS_CONTINUE_READING;
 err:
    BIO_free(s->s3.handshake_buffer);
    s->s3.handshake_buffer = NULL;
    EVP_MD_CTX_free(mctx);
#ifndef OPENSSL_NO_GOST
    OPENSSL_free(gost_data);
#endif
    return ret;
}