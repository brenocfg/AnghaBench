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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {int /*<<< orphan*/  login; } ;
struct TYPE_6__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_contains_zero_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_strndup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_SRP ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_ctos_srp(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    PACKET srp_I;

    if (!PACKET_as_length_prefixed_1(pkt, &srp_I)
            || PACKET_contains_zero_byte(&srp_I)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_SRP,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    /*
     * TODO(openssl-team): currently, we re-authenticate the user
     * upon resumption. Instead, we MUST ignore the login.
     */
    if (!PACKET_strndup(&srp_I, &s->srp_ctx.login)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_SRP,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}