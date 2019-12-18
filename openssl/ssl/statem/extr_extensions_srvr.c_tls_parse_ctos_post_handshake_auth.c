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
struct TYPE_4__ {int /*<<< orphan*/  post_handshake_auth; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_POST_HANDSHAKE_AUTH ; 
 int /*<<< orphan*/  SSL_PHA_EXT_RECEIVED ; 
 int /*<<< orphan*/  SSL_R_POST_HANDSHAKE_AUTH_ENCODING_ERR ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_ctos_post_handshake_auth(SSL *s, PACKET *pkt, unsigned int context,
                                       X509 *x, size_t chainidx)
{
    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_POST_HANDSHAKE_AUTH,
                 SSL_R_POST_HANDSHAKE_AUTH_ENCODING_ERR);
        return 0;
    }

    s->post_handshake_auth = SSL_PHA_EXT_RECEIVED;

    return 1;
}