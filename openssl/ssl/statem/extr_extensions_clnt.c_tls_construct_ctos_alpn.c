#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {int alpn_sent; } ;
struct TYPE_8__ {int /*<<< orphan*/  alpn_len; int /*<<< orphan*/ * alpn; } ;
struct TYPE_9__ {TYPE_1__ s3; TYPE_2__ ext; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_ALPN ; 
 int /*<<< orphan*/  SSL_IS_FIRST_HANDSHAKE (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_application_layer_protocol_negotiation ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_ctos_alpn(SSL *s, WPACKET *pkt, unsigned int context,
                                   X509 *x, size_t chainidx)
{
    s->s3.alpn_sent = 0;

    if (s->ext.alpn == NULL || !SSL_IS_FIRST_HANDSHAKE(s))
        return EXT_RETURN_NOT_SENT;

    if (!WPACKET_put_bytes_u16(pkt,
                TLSEXT_TYPE_application_layer_protocol_negotiation)
               /* Sub-packet ALPN extension */
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_sub_memcpy_u16(pkt, s->ext.alpn, s->ext.alpn_len)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_ALPN,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    s->s3.alpn_sent = 1;

    return EXT_RETURN_SENT;
}