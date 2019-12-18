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
struct TYPE_4__ {int options; scalar_t__ renegotiate; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_F_FINAL_RENEGOTIATE ; 
 int SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION ; 
 int SSL_OP_LEGACY_SERVER_CONNECT ; 
 int /*<<< orphan*/  SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int final_renegotiate(SSL *s, unsigned int context, int sent)
{
    if (!s->server) {
        /*
         * Check if we can connect to a server that doesn't support safe
         * renegotiation
         */
        if (!(s->options & SSL_OP_LEGACY_SERVER_CONNECT)
                && !(s->options & SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION)
                && !sent) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_FINAL_RENEGOTIATE,
                     SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED);
            return 0;
        }

        return 1;
    }

    /* Need RI if renegotiating */
    if (s->renegotiate
            && !(s->options & SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION)
            && !sent) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_FINAL_RENEGOTIATE,
                 SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED);
        return 0;
    }


    return 1;
}