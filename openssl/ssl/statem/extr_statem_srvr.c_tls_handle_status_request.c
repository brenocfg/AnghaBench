#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  resp; } ;
struct TYPE_18__ {int status_expected; scalar_t__ status_type; TYPE_6__ ocsp; } ;
struct TYPE_13__ {int /*<<< orphan*/ * cert; } ;
struct TYPE_14__ {TYPE_2__ tmp; } ;
struct TYPE_19__ {TYPE_7__ ext; TYPE_5__* ctx; TYPE_3__ s3; TYPE_1__* cert; } ;
struct TYPE_15__ {int (* status_cb ) (TYPE_8__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  status_arg; } ;
struct TYPE_16__ {TYPE_4__ ext; } ;
struct TYPE_12__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_8__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_HANDLE_STATUS_REQUEST ; 
 int /*<<< orphan*/  SSL_R_CLIENTHELLO_TLSEXT ; 
#define  SSL_TLSEXT_ERR_ALERT_FATAL 130 
#define  SSL_TLSEXT_ERR_NOACK 129 
#define  SSL_TLSEXT_ERR_OK 128 
 int /*<<< orphan*/  SSLfatal (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_STATUSTYPE_nothing ; 
 int stub1 (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_handle_status_request(SSL *s)
{
    s->ext.status_expected = 0;

    /*
     * If status request then ask callback what to do. Note: this must be
     * called after servername callbacks in case the certificate has changed,
     * and must be called after the cipher has been chosen because this may
     * influence which certificate is sent
     */
    if (s->ext.status_type != TLSEXT_STATUSTYPE_nothing && s->ctx != NULL
            && s->ctx->ext.status_cb != NULL) {
        int ret;

        /* If no certificate can't return certificate status */
        if (s->s3.tmp.cert != NULL) {
            /*
             * Set current certificate to one we will use so SSL_get_certificate
             * et al can pick it up.
             */
            s->cert->key = s->s3.tmp.cert;
            ret = s->ctx->ext.status_cb(s, s->ctx->ext.status_arg);
            switch (ret) {
                /* We don't want to send a status request response */
            case SSL_TLSEXT_ERR_NOACK:
                s->ext.status_expected = 0;
                break;
                /* status request response should be sent */
            case SSL_TLSEXT_ERR_OK:
                if (s->ext.ocsp.resp)
                    s->ext.status_expected = 1;
                break;
                /* something bad happened */
            case SSL_TLSEXT_ERR_ALERT_FATAL:
            default:
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_HANDLE_STATUS_REQUEST,
                         SSL_R_CLIENTHELLO_TLSEXT);
                return 0;
            }
        }
    }

    return 1;
}