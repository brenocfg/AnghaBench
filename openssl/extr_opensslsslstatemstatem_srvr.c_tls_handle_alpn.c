#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ early_data_ok; } ;
struct TYPE_13__ {unsigned char alpn_selected_len; scalar_t__ npn_seen; int /*<<< orphan*/ * alpn_selected; scalar_t__ alpn_proposed_len; int /*<<< orphan*/ * alpn_proposed; } ;
struct TYPE_17__ {TYPE_6__ ext; TYPE_5__* session; int /*<<< orphan*/  hit; TYPE_3__ s3; TYPE_2__* ctx; } ;
struct TYPE_14__ {unsigned char alpn_selected_len; int /*<<< orphan*/ * alpn_selected; } ;
struct TYPE_15__ {TYPE_4__ ext; } ;
struct TYPE_11__ {int (* alpn_select_cb ) (TYPE_7__*,unsigned char const**,unsigned char*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  alpn_select_cb_arg; } ;
struct TYPE_12__ {TYPE_1__ ext; } ;
typedef  TYPE_7__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 void* OPENSSL_memdup (unsigned char const*,unsigned char) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_NO_APPLICATION_PROTOCOL ; 
 int /*<<< orphan*/  SSL_F_TLS_HANDLE_ALPN ; 
 int /*<<< orphan*/  SSL_R_NO_APPLICATION_PROTOCOL ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_7__*,unsigned char const**,unsigned char*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

int tls_handle_alpn(SSL *s)
{
    const unsigned char *selected = NULL;
    unsigned char selected_len = 0;

    if (s->ctx->ext.alpn_select_cb != NULL && s->s3.alpn_proposed != NULL) {
        int r = s->ctx->ext.alpn_select_cb(s, &selected, &selected_len,
                                           s->s3.alpn_proposed,
                                           (unsigned int)s->s3.alpn_proposed_len,
                                           s->ctx->ext.alpn_select_cb_arg);

        if (r == SSL_TLSEXT_ERR_OK) {
            OPENSSL_free(s->s3.alpn_selected);
            s->s3.alpn_selected = OPENSSL_memdup(selected, selected_len);
            if (s->s3.alpn_selected == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_HANDLE_ALPN,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
            s->s3.alpn_selected_len = selected_len;
#ifndef OPENSSL_NO_NEXTPROTONEG
            /* ALPN takes precedence over NPN. */
            s->s3.npn_seen = 0;
#endif

            /* Check ALPN is consistent with session */
            if (s->session->ext.alpn_selected == NULL
                        || selected_len != s->session->ext.alpn_selected_len
                        || memcmp(selected, s->session->ext.alpn_selected,
                                  selected_len) != 0) {
                /* Not consistent so can't be used for early_data */
                s->ext.early_data_ok = 0;

                if (!s->hit) {
                    /*
                     * This is a new session and so alpn_selected should have
                     * been initialised to NULL. We should update it with the
                     * selected ALPN.
                     */
                    if (!ossl_assert(s->session->ext.alpn_selected == NULL)) {
                        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                                 SSL_F_TLS_HANDLE_ALPN,
                                 ERR_R_INTERNAL_ERROR);
                        return 0;
                    }
                    s->session->ext.alpn_selected = OPENSSL_memdup(selected,
                                                                   selected_len);
                    if (s->session->ext.alpn_selected == NULL) {
                        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                                 SSL_F_TLS_HANDLE_ALPN,
                                 ERR_R_INTERNAL_ERROR);
                        return 0;
                    }
                    s->session->ext.alpn_selected_len = selected_len;
                }
            }

            return 1;
        } else if (r != SSL_TLSEXT_ERR_NOACK) {
            SSLfatal(s, SSL_AD_NO_APPLICATION_PROTOCOL, SSL_F_TLS_HANDLE_ALPN,
                     SSL_R_NO_APPLICATION_PROTOCOL);
            return 0;
        }
        /*
         * If r == SSL_TLSEXT_ERR_NOACK then behave as if no callback was
         * present.
         */
    }

    /* Check ALPN is consistent with session */
    if (s->session->ext.alpn_selected != NULL) {
        /* Not consistent so can't be used for early_data */
        s->ext.early_data_ok = 0;
    }

    return 1;
}