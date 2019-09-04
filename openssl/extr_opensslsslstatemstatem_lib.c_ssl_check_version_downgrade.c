#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ version; int /*<<< orphan*/  (* smeth ) () ;} ;
typedef  TYPE_3__ version_info ;
struct TYPE_16__ {scalar_t__ version; } ;
struct TYPE_15__ {scalar_t__ version; TYPE_2__* ctx; } ;
struct TYPE_13__ {TYPE_1__* method; } ;
struct TYPE_12__ {scalar_t__ version; } ;
struct TYPE_11__ {scalar_t__ version; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 TYPE_10__* DTLS_method () ; 
 TYPE_9__* TLS_method () ; 
 TYPE_3__* dtls_version_table ; 
 scalar_t__ ssl_method_error (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_3__* tls_version_table ; 

int ssl_check_version_downgrade(SSL *s)
{
    const version_info *vent;
    const version_info *table;

    /*
     * Check that the current protocol is the highest enabled version
     * (according to s->ctx->method, as version negotiation may have changed
     * s->method).
     */
    if (s->version == s->ctx->method->version)
        return 1;

    /*
     * Apparently we're using a version-flexible SSL_METHOD (not at its
     * highest protocol version).
     */
    if (s->ctx->method->version == TLS_method()->version)
        table = tls_version_table;
    else if (s->ctx->method->version == DTLS_method()->version)
        table = dtls_version_table;
    else {
        /* Unexpected state; fail closed. */
        return 0;
    }

    for (vent = table; vent->version != 0; ++vent) {
        if (vent->smeth != NULL && ssl_method_error(s, vent->smeth()) == 0)
            return s->version == vent->version;
    }
    return 0;
}