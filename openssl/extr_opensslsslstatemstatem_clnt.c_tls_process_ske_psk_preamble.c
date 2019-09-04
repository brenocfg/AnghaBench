#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* session; } ;
struct TYPE_5__ {int /*<<< orphan*/ * psk_identity_hint; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_strndup (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ PSK_MAX_IDENTITY_LEN ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_SKE_PSK_PREAMBLE ; 
 int /*<<< orphan*/  SSL_R_DATA_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_process_ske_psk_preamble(SSL *s, PACKET *pkt)
{
#ifndef OPENSSL_NO_PSK
    PACKET psk_identity_hint;

    /* PSK ciphersuites are preceded by an identity hint */

    if (!PACKET_get_length_prefixed_2(pkt, &psk_identity_hint)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_SKE_PSK_PREAMBLE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    /*
     * Store PSK identity hint for later use, hint is used in
     * tls_construct_client_key_exchange.  Assume that the maximum length of
     * a PSK identity hint can be as long as the maximum length of a PSK
     * identity.
     */
    if (PACKET_remaining(&psk_identity_hint) > PSK_MAX_IDENTITY_LEN) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                 SSL_F_TLS_PROCESS_SKE_PSK_PREAMBLE,
                 SSL_R_DATA_LENGTH_TOO_LONG);
        return 0;
    }

    if (PACKET_remaining(&psk_identity_hint) == 0) {
        OPENSSL_free(s->session->psk_identity_hint);
        s->session->psk_identity_hint = NULL;
    } else if (!PACKET_strndup(&psk_identity_hint,
                               &s->session->psk_identity_hint)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_PSK_PREAMBLE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_PSK_PREAMBLE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}