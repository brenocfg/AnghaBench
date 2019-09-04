#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_4__ {int /*<<< orphan*/  post_handshake_auth; int /*<<< orphan*/  pha_enabled; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_POST_HANDSHAKE_AUTH ; 
 int /*<<< orphan*/  SSL_PHA_EXT_SENT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_post_handshake_auth ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 

EXT_RETURN tls_construct_ctos_post_handshake_auth(SSL *s, WPACKET *pkt,
                                                  unsigned int context,
                                                  X509 *x, size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    if (!s->pha_enabled)
        return EXT_RETURN_NOT_SENT;

    /* construct extension - 0 length, no contents */
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_post_handshake_auth)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_POST_HANDSHAKE_AUTH,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    s->post_handshake_auth = SSL_PHA_EXT_SENT;

    return EXT_RETURN_SENT;
#else
    return EXT_RETURN_NOT_SENT;
#endif
}