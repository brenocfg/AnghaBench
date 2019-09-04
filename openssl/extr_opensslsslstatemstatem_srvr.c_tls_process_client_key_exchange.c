#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * psk; int /*<<< orphan*/  psklen; TYPE_1__* new_cipher; } ;
struct TYPE_16__ {TYPE_2__ tmp; } ;
struct TYPE_17__ {TYPE_3__ s3; } ;
struct TYPE_14__ {unsigned long algorithm_mkey; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_PROCESSING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CLIENT_KEY_EXCHANGE ; 
 unsigned long SSL_PSK ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_UNKNOWN_CIPHER_TYPE ; 
 unsigned long SSL_kDHE ; 
 unsigned long SSL_kDHEPSK ; 
 unsigned long SSL_kECDHE ; 
 unsigned long SSL_kECDHEPSK ; 
 unsigned long SSL_kGOST ; 
 unsigned long SSL_kPSK ; 
 unsigned long SSL_kRSA ; 
 unsigned long SSL_kRSAPSK ; 
 unsigned long SSL_kSRP ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_generate_master_secret (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_process_cke_dhe (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cke_ecdhe (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cke_gost (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cke_psk_preamble (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cke_rsa (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cke_srp (TYPE_4__*,int /*<<< orphan*/ *) ; 

MSG_PROCESS_RETURN tls_process_client_key_exchange(SSL *s, PACKET *pkt)
{
    unsigned long alg_k;

    alg_k = s->s3.tmp.new_cipher->algorithm_mkey;

    /* For PSK parse and retrieve identity, obtain PSK key */
    if ((alg_k & SSL_PSK) && !tls_process_cke_psk_preamble(s, pkt)) {
        /* SSLfatal() already called */
        goto err;
    }

    if (alg_k & SSL_kPSK) {
        /* Identity extracted earlier: should be nothing left */
        if (PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CLIENT_KEY_EXCHANGE,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }
        /* PSK handled by ssl_generate_master_secret */
        if (!ssl_generate_master_secret(s, NULL, 0, 0)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & (SSL_kRSA | SSL_kRSAPSK)) {
        if (!tls_process_cke_rsa(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & (SSL_kDHE | SSL_kDHEPSK)) {
        if (!tls_process_cke_dhe(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & (SSL_kECDHE | SSL_kECDHEPSK)) {
        if (!tls_process_cke_ecdhe(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & SSL_kSRP) {
        if (!tls_process_cke_srp(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else if (alg_k & SSL_kGOST) {
        if (!tls_process_cke_gost(s, pkt)) {
            /* SSLfatal() already called */
            goto err;
        }
    } else {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_PROCESS_CLIENT_KEY_EXCHANGE,
                 SSL_R_UNKNOWN_CIPHER_TYPE);
        goto err;
    }

    return MSG_PROCESS_CONTINUE_PROCESSING;
 err:
#ifndef OPENSSL_NO_PSK
    OPENSSL_clear_free(s->s3.tmp.psk, s->s3.tmp.psklen);
    s->s3.tmp.psk = NULL;
#endif
    return MSG_PROCESS_ERROR;
}