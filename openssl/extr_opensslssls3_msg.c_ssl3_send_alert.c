#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int alert_dispatch; int* send_alert; } ;
struct TYPE_11__ {scalar_t__ version; TYPE_3__* method; int /*<<< orphan*/  rlayer; TYPE_2__ s3; int /*<<< orphan*/ * session; int /*<<< orphan*/  session_ctx; } ;
struct TYPE_10__ {int (* ssl_dispatch_alert ) (TYPE_4__*) ;TYPE_1__* ssl3_enc; } ;
struct TYPE_8__ {int (* alert_value ) (int) ;} ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_LAYER_write_pending (int /*<<< orphan*/ *) ; 
 int SSL3_AL_FATAL ; 
 scalar_t__ SSL3_VERSION ; 
 int SSL_AD_HANDSHAKE_FAILURE ; 
 int SSL_AD_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  SSL_CTX_remove_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_TREAT_AS_TLS13 (TYPE_4__*) ; 
 int stub1 (int) ; 
 int stub2 (TYPE_4__*) ; 
 int tls13_alert_code (int) ; 

int ssl3_send_alert(SSL *s, int level, int desc)
{
    /* Map tls/ssl alert value to correct one */
    if (SSL_TREAT_AS_TLS13(s))
        desc = tls13_alert_code(desc);
    else
        desc = s->method->ssl3_enc->alert_value(desc);
    if (s->version == SSL3_VERSION && desc == SSL_AD_PROTOCOL_VERSION)
        desc = SSL_AD_HANDSHAKE_FAILURE; /* SSL 3.0 does not have
                                          * protocol_version alerts */
    if (desc < 0)
        return -1;
    /* If a fatal one, remove from cache */
    if ((level == SSL3_AL_FATAL) && (s->session != NULL))
        SSL_CTX_remove_session(s->session_ctx, s->session);

    s->s3.alert_dispatch = 1;
    s->s3.send_alert[0] = level;
    s->s3.send_alert[1] = desc;
    if (!RECORD_LAYER_write_pending(&s->rlayer)) {
        /* data still being written out? */
        return s->method->ssl_dispatch_alert(s);
    }
    /*
     * else data is still being written out, we will get written some time in
     * the future
     */
    return -1;
}