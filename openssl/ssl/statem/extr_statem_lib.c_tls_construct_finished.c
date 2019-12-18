#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_18__ {scalar_t__ cert_req; size_t finish_md_len; int /*<<< orphan*/  finish_md; } ;
struct TYPE_19__ {size_t previous_client_finished_len; size_t previous_server_finished_len; TYPE_5__ tmp; int /*<<< orphan*/  previous_server_finished; int /*<<< orphan*/  previous_client_finished; } ;
struct TYPE_14__ {int cleanuphand; } ;
struct TYPE_20__ {scalar_t__ post_handshake_auth; TYPE_6__ s3; scalar_t__ server; TYPE_4__* session; TYPE_3__* method; TYPE_1__ statem; } ;
struct TYPE_17__ {int /*<<< orphan*/  master_key_length; int /*<<< orphan*/  master_key; } ;
struct TYPE_16__ {TYPE_2__* ssl3_enc; } ;
struct TYPE_15__ {char* server_finished_label; size_t server_finished_label_len; char* client_finished_label; size_t client_finished_label_len; size_t (* final_finish_mac ) (TYPE_7__*,char const*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* change_cipher_state ) (TYPE_7__*,int) ;} ;
typedef  TYPE_7__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 size_t EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  MASTER_SECRET_LABEL ; 
 int SSL3_CC_HANDSHAKE ; 
 int SSL3_CHANGE_CIPHER_CLIENT_WRITE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_FINISHED ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_7__*) ; 
 scalar_t__ SSL_PHA_REQUESTED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ssl_log_secret (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int) ; 
 size_t stub2 (TYPE_7__*,char const*,size_t,int /*<<< orphan*/ ) ; 

int tls_construct_finished(SSL *s, WPACKET *pkt)
{
    size_t finish_md_len;
    const char *sender;
    size_t slen;

    /* This is a real handshake so make sure we clean it up at the end */
    if (!s->server && s->post_handshake_auth != SSL_PHA_REQUESTED)
        s->statem.cleanuphand = 1;

    /*
     * We only change the keys if we didn't already do this when we sent the
     * client certificate
     */
    if (SSL_IS_TLS13(s)
            && !s->server
            && s->s3.tmp.cert_req == 0
            && (!s->method->ssl3_enc->change_cipher_state(s,
                    SSL3_CC_HANDSHAKE | SSL3_CHANGE_CIPHER_CLIENT_WRITE))) {;
        /* SSLfatal() already called */
        return 0;
    }

    if (s->server) {
        sender = s->method->ssl3_enc->server_finished_label;
        slen = s->method->ssl3_enc->server_finished_label_len;
    } else {
        sender = s->method->ssl3_enc->client_finished_label;
        slen = s->method->ssl3_enc->client_finished_label_len;
    }

    finish_md_len = s->method->ssl3_enc->final_finish_mac(s,
                                                          sender, slen,
                                                          s->s3.tmp.finish_md);
    if (finish_md_len == 0) {
        /* SSLfatal() already called */
        return 0;
    }

    s->s3.tmp.finish_md_len = finish_md_len;

    if (!WPACKET_memcpy(pkt, s->s3.tmp.finish_md, finish_md_len)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_FINISHED,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /*
     * Log the master secret, if logging is enabled. We don't log it for
     * TLSv1.3: there's a different key schedule for that.
     */
    if (!SSL_IS_TLS13(s) && !ssl_log_secret(s, MASTER_SECRET_LABEL,
                                            s->session->master_key,
                                            s->session->master_key_length)) {
        /* SSLfatal() already called */
        return 0;
    }

    /*
     * Copy the finished so we can use it for renegotiation checks
     */
    if (!ossl_assert(finish_md_len <= EVP_MAX_MD_SIZE)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_FINISHED,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (!s->server) {
        memcpy(s->s3.previous_client_finished, s->s3.tmp.finish_md,
               finish_md_len);
        s->s3.previous_client_finished_len = finish_md_len;
    } else {
        memcpy(s->s3.previous_server_finished, s->s3.tmp.finish_md,
               finish_md_len);
        s->s3.previous_server_finished_len = finish_md_len;
    }

    return 1;
}