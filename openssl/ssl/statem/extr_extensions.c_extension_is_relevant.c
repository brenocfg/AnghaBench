#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ version; scalar_t__ hit; scalar_t__ server; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 scalar_t__ SSL3_VERSION ; 
 unsigned int SSL_EXT_CLIENT_HELLO ; 
 unsigned int SSL_EXT_IGNORE_ON_RESUMPTION ; 
 unsigned int SSL_EXT_SSL3_ALLOWED ; 
 unsigned int SSL_EXT_TLS1_2_AND_BELOW_ONLY ; 
 unsigned int SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST ; 
 unsigned int SSL_EXT_TLS1_3_ONLY ; 
 unsigned int SSL_EXT_TLS_IMPLEMENTATION_ONLY ; 
 scalar_t__ SSL_IS_DTLS (TYPE_1__*) ; 
 int SSL_IS_TLS13 (TYPE_1__*) ; 

int extension_is_relevant(SSL *s, unsigned int extctx, unsigned int thisctx)
{
    int is_tls13;

    /*
     * For HRR we haven't selected the version yet but we know it will be
     * TLSv1.3
     */
    if ((thisctx & SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST) != 0)
        is_tls13 = 1;
    else
        is_tls13 = SSL_IS_TLS13(s);

    if ((SSL_IS_DTLS(s)
                && (extctx & SSL_EXT_TLS_IMPLEMENTATION_ONLY) != 0)
            || (s->version == SSL3_VERSION
                    && (extctx & SSL_EXT_SSL3_ALLOWED) == 0)
            /*
             * Note that SSL_IS_TLS13() means "TLS 1.3 has been negotiated",
             * which is never true when generating the ClientHello.
             * However, version negotiation *has* occurred by the time the
             * ClientHello extensions are being parsed.
             * Be careful to allow TLS 1.3-only extensions when generating
             * the ClientHello.
             */
            || (is_tls13 && (extctx & SSL_EXT_TLS1_2_AND_BELOW_ONLY) != 0)
            || (!is_tls13 && (extctx & SSL_EXT_TLS1_3_ONLY) != 0
                && (thisctx & SSL_EXT_CLIENT_HELLO) == 0)
            || (s->server && !is_tls13 && (extctx & SSL_EXT_TLS1_3_ONLY) != 0)
            || (s->hit && (extctx & SSL_EXT_IGNORE_ON_RESUMPTION) != 0))
        return 0;
    return 1;
}