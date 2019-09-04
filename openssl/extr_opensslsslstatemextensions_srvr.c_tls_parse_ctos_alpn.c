#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int /*<<< orphan*/  alpn_proposed_len; int /*<<< orphan*/ * alpn_proposed; } ;
struct TYPE_7__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_ALPN ; 
 int /*<<< orphan*/  SSL_IS_FIRST_HANDSHAKE (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_ctos_alpn(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                        size_t chainidx)
{
    PACKET protocol_list, save_protocol_list, protocol;

    if (!SSL_IS_FIRST_HANDSHAKE(s))
        return 1;

    if (!PACKET_as_length_prefixed_2(pkt, &protocol_list)
        || PACKET_remaining(&protocol_list) < 2) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_ALPN,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    save_protocol_list = protocol_list;
    do {
        /* Protocol names can't be empty. */
        if (!PACKET_get_length_prefixed_1(&protocol_list, &protocol)
                || PACKET_remaining(&protocol) == 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_ALPN,
                     SSL_R_BAD_EXTENSION);
            return 0;
        }
    } while (PACKET_remaining(&protocol_list) != 0);

    OPENSSL_free(s->s3.alpn_proposed);
    s->s3.alpn_proposed = NULL;
    s->s3.alpn_proposed_len = 0;
    if (!PACKET_memdup(&save_protocol_list,
                       &s->s3.alpn_proposed, &s->s3.alpn_proposed_len)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_ALPN,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}