#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* new_cipher; int /*<<< orphan*/  peer_sigalg; } ;
struct TYPE_19__ {TYPE_2__ tmp; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_20__ {TYPE_3__ s3; } ;
struct TYPE_17__ {long algorithm_mkey; int algorithm_auth; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*,size_t) ; 
 scalar_t__ EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  OSSL_TRACE1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_sub_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_SALTLEN_DIGEST ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_DECRYPT_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_KEY_EXCHANGE ; 
 long SSL_PSK ; 
 int /*<<< orphan*/  SSL_R_BAD_DATA ; 
 int /*<<< orphan*/  SSL_R_BAD_SIGNATURE ; 
 int /*<<< orphan*/  SSL_R_EXTRA_DATA_IN_MESSAGE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_LENGTH_TOO_SHORT ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_R_WRONG_SIGNATURE_LENGTH ; 
 scalar_t__ SSL_USE_PSS (TYPE_4__*) ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_4__*) ; 
 int SSL_aNULL ; 
 int SSL_aSRP ; 
 long SSL_kDHE ; 
 long SSL_kDHEPSK ; 
 long SSL_kECDHE ; 
 long SSL_kECDHEPSK ; 
 long SSL_kPSK ; 
 long SSL_kRSAPSK ; 
 long SSL_kSRP ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS ; 
 size_t construct_key_exchange_tbs (TYPE_4__*,unsigned char**,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ssl3_check_cert_and_algorithm (TYPE_4__*) ; 
 scalar_t__ tls12_check_peer_sigalg (TYPE_4__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_lookup_md (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  tls1_set_peer_legacy_sigalg (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_ske_dhe (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tls_process_ske_ecdhe (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tls_process_ske_psk_preamble (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_ske_srp (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

MSG_PROCESS_RETURN tls_process_key_exchange(SSL *s, PACKET *pkt)
{
    long alg_k;
    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *md_ctx = NULL;
    EVP_PKEY_CTX *pctx = NULL;
    PACKET save_param_start, signature;

    alg_k = s->s3.tmp.new_cipher->algorithm_mkey;

    save_param_start = *pkt;

#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    EVP_PKEY_free(s->s3.peer_tmp);
    s->s3.peer_tmp = NULL;
#endif

    if (alg_k & SSL_PSK) {
        if (!tls_process_ske_psk_preamble(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    }

    /* Nothing else to do for plain PSK or RSAPSK */
    if (alg_k & (SSL_kPSK | SSL_kRSAPSK)) {
    } else if (alg_k & SSL_kSRP) {
        if (!tls_process_ske_srp(s, pkt, &pkey)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & (SSL_kDHE | SSL_kDHEPSK)) {
        if (!tls_process_ske_dhe(s, pkt, &pkey)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & (SSL_kECDHE | SSL_kECDHEPSK)) {
        if (!tls_process_ske_ecdhe(s, pkt, &pkey)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k) {
        SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                 SSL_R_UNEXPECTED_MESSAGE);
        goto err;
    }

    /* if it was signed, check the signature */
    if (pkey != NULL) {
        PACKET params;
        int maxsig;
        const EVP_MD *md = NULL;
        unsigned char *tbs;
        size_t tbslen;
        int rv;

        /*
         * |pkt| now points to the beginning of the signature, so the difference
         * equals the length of the parameters.
         */
        if (!PACKET_get_sub_packet(&save_param_start, &params,
                                   PACKET_remaining(&save_param_start) -
                                   PACKET_remaining(pkt))) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        if (SSL_USE_SIGALGS(s)) {
            unsigned int sigalg;

            if (!PACKET_get_net_2(pkt, &sigalg)) {
                SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                         SSL_R_LENGTH_TOO_SHORT);
                goto err;
            }
            if (tls12_check_peer_sigalg(s, sigalg, pkey) <=0) {
                /* SSLfatal() already called */
                goto err;
            }
        } else if (!tls1_set_peer_legacy_sigalg(s, pkey)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        if (!tls1_lookup_md(s->s3.tmp.peer_sigalg, &md)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        if (SSL_USE_SIGALGS(s))
            OSSL_TRACE1(TLS, "USING TLSv1.2 HASH %s\n",
                        md == NULL ? "n/a" : EVP_MD_name(md));

        if (!PACKET_get_length_prefixed_2(pkt, &signature)
            || PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }
        maxsig = EVP_PKEY_size(pkey);
        if (maxsig < 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        /*
         * Check signature length
         */
        if (PACKET_remaining(&signature) > (size_t)maxsig) {
            /* wrong packet length */
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                   SSL_R_WRONG_SIGNATURE_LENGTH);
            goto err;
        }

        md_ctx = EVP_MD_CTX_new();
        if (md_ctx == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        }

        if (EVP_DigestVerifyInit(md_ctx, &pctx, md, NULL, pkey) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     ERR_R_EVP_LIB);
            goto err;
        }
        if (SSL_USE_PSS(s)) {
            if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) <= 0
                || EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx,
                                                RSA_PSS_SALTLEN_DIGEST) <= 0) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_PROCESS_KEY_EXCHANGE, ERR_R_EVP_LIB);
                goto err;
            }
        }
        tbslen = construct_key_exchange_tbs(s, &tbs, PACKET_data(&params),
                                            PACKET_remaining(&params));
        if (tbslen == 0) {
            /* SSLfatal() already called */
            goto err;
        }

        rv = EVP_DigestVerify(md_ctx, PACKET_data(&signature),
                              PACKET_remaining(&signature), tbs, tbslen);
        OPENSSL_free(tbs);
        if (rv <= 0) {
            SSLfatal(s, SSL_AD_DECRYPT_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     SSL_R_BAD_SIGNATURE);
            goto err;
        }
        EVP_MD_CTX_free(md_ctx);
        md_ctx = NULL;
    } else {
        /* aNULL, aSRP or PSK do not need public keys */
        if (!(s->s3.tmp.new_cipher->algorithm_auth & (SSL_aNULL | SSL_aSRP))
            && !(alg_k & SSL_PSK)) {
            /* Might be wrong key type, check it */
            if (ssl3_check_cert_and_algorithm(s)) {
                SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                         SSL_R_BAD_DATA);
            }
            /* else this shouldn't happen, SSLfatal() already called */
            goto err;
        }
        /* still data left over */
        if (PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_KEY_EXCHANGE,
                     SSL_R_EXTRA_DATA_IN_MESSAGE);
            goto err;
        }
    }

    return MSG_PROCESS_CONTINUE_READING;
 err:
    EVP_MD_CTX_free(md_ctx);
    return MSG_PROCESS_ERROR;
}