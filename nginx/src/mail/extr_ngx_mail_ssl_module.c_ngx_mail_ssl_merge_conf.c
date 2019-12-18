#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_40__ {TYPE_5__* data; int /*<<< orphan*/  (* handler ) (TYPE_5__*) ;} ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
struct TYPE_43__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  log; } ;
struct TYPE_44__ {scalar_t__ len; } ;
struct TYPE_41__ {scalar_t__ starttls; scalar_t__ verify; scalar_t__ verify_depth; TYPE_9__* session_ticket_keys; TYPE_5__ ssl; scalar_t__ session_tickets; scalar_t__ session_timeout; int /*<<< orphan*/ * shm_zone; scalar_t__ builtin_session_cache; TYPE_9__* certificates; TYPE_6__ ecdh_curve; TYPE_6__ dhparam; scalar_t__ prefer_server_ciphers; TYPE_6__ ciphers; TYPE_6__ crl; TYPE_6__ trusted_certificate; TYPE_6__ client_certificate; TYPE_9__* passwords; TYPE_9__* certificate_keys; int /*<<< orphan*/  protocols; int /*<<< orphan*/  line; int /*<<< orphan*/ * file; scalar_t__ enable; scalar_t__ listen; } ;
typedef  TYPE_2__ ngx_mail_ssl_conf_t ;
struct TYPE_42__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;
struct TYPE_45__ {scalar_t__ nelts; scalar_t__ elts; } ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 char* NGX_DEFAULT_CIPHERS ; 
 char* NGX_DEFAULT_ECDH_CURVE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_MAIL_STARTTLS_OFF ; 
 scalar_t__ NGX_OK ; 
 int NGX_SSL_NONE_SCACHE ; 
 int NGX_SSL_TLSv1 ; 
 int NGX_SSL_TLSv1_1 ; 
 int NGX_SSL_TLSv1_2 ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_NO_TICKET ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (TYPE_9__*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (TYPE_6__,TYPE_6__,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_mail_ssl_sess_id_ctx ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_ssl_certificates (TYPE_3__*,TYPE_5__*,TYPE_9__*,TYPE_9__*,TYPE_9__*) ; 
 scalar_t__ ngx_ssl_ciphers (TYPE_3__*,TYPE_5__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_ssl_cleanup_ctx (TYPE_5__*) ; 
 scalar_t__ ngx_ssl_client_certificate (TYPE_3__*,TYPE_5__*,TYPE_6__*,scalar_t__) ; 
 scalar_t__ ngx_ssl_create (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_ssl_crl (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_dhparam (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_ecdh_curve (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_session_cache (TYPE_5__*,int /*<<< orphan*/ *,TYPE_9__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ngx_ssl_session_ticket_keys (TYPE_3__*,TYPE_5__*,TYPE_9__*) ; 
 scalar_t__ ngx_ssl_trusted_certificate (TYPE_3__*,TYPE_5__*,TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static char *
ngx_mail_ssl_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_mail_ssl_conf_t *prev = parent;
    ngx_mail_ssl_conf_t *conf = child;

    char                *mode;
    ngx_pool_cleanup_t  *cln;

    ngx_conf_merge_value(conf->enable, prev->enable, 0);
    ngx_conf_merge_uint_value(conf->starttls, prev->starttls,
                         NGX_MAIL_STARTTLS_OFF);

    ngx_conf_merge_value(conf->session_timeout,
                         prev->session_timeout, 300);

    ngx_conf_merge_value(conf->prefer_server_ciphers,
                         prev->prefer_server_ciphers, 0);

    ngx_conf_merge_bitmask_value(conf->protocols, prev->protocols,
                         (NGX_CONF_BITMASK_SET|NGX_SSL_TLSv1
                          |NGX_SSL_TLSv1_1|NGX_SSL_TLSv1_2));

    ngx_conf_merge_uint_value(conf->verify, prev->verify, 0);
    ngx_conf_merge_uint_value(conf->verify_depth, prev->verify_depth, 1);

    ngx_conf_merge_ptr_value(conf->certificates, prev->certificates, NULL);
    ngx_conf_merge_ptr_value(conf->certificate_keys, prev->certificate_keys,
                         NULL);

    ngx_conf_merge_ptr_value(conf->passwords, prev->passwords, NULL);

    ngx_conf_merge_str_value(conf->dhparam, prev->dhparam, "");

    ngx_conf_merge_str_value(conf->ecdh_curve, prev->ecdh_curve,
                         NGX_DEFAULT_ECDH_CURVE);

    ngx_conf_merge_str_value(conf->client_certificate,
                         prev->client_certificate, "");
    ngx_conf_merge_str_value(conf->trusted_certificate,
                         prev->trusted_certificate, "");
    ngx_conf_merge_str_value(conf->crl, prev->crl, "");

    ngx_conf_merge_str_value(conf->ciphers, prev->ciphers, NGX_DEFAULT_CIPHERS);


    conf->ssl.log = cf->log;

    if (conf->listen) {
        mode = "listen ... ssl";

    } else if (conf->enable) {
        mode = "ssl";

    } else if (conf->starttls != NGX_MAIL_STARTTLS_OFF) {
        mode = "starttls";

    } else {
        return NGX_CONF_OK;
    }

    if (conf->file == NULL) {
        conf->file = prev->file;
        conf->line = prev->line;
    }

    if (conf->certificates == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no \"ssl_certificate\" is defined for "
                      "the \"%s\" directive in %s:%ui",
                      mode, conf->file, conf->line);
        return NGX_CONF_ERROR;
    }

    if (conf->certificate_keys == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no \"ssl_certificate_key\" is defined for "
                      "the \"%s\" directive in %s:%ui",
                      mode, conf->file, conf->line);
        return NGX_CONF_ERROR;
    }

    if (conf->certificate_keys->nelts < conf->certificates->nelts) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no \"ssl_certificate_key\" is defined "
                      "for certificate \"%V\" and "
                      "the \"%s\" directive in %s:%ui",
                      ((ngx_str_t *) conf->certificates->elts)
                      + conf->certificates->nelts - 1,
                      mode, conf->file, conf->line);
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_create(&conf->ssl, conf->protocols, NULL) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    cln = ngx_pool_cleanup_add(cf->pool, 0);
    if (cln == NULL) {
        ngx_ssl_cleanup_ctx(&conf->ssl);
        return NGX_CONF_ERROR;
    }

    cln->handler = ngx_ssl_cleanup_ctx;
    cln->data = &conf->ssl;

    if (ngx_ssl_certificates(cf, &conf->ssl, conf->certificates,
                             conf->certificate_keys, conf->passwords)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    if (conf->verify) {

        if (conf->client_certificate.len == 0 && conf->verify != 3) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no ssl_client_certificate for ssl_verify_client");
            return NGX_CONF_ERROR;
        }

        if (ngx_ssl_client_certificate(cf, &conf->ssl,
                                       &conf->client_certificate,
                                       conf->verify_depth)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

        if (ngx_ssl_trusted_certificate(cf, &conf->ssl,
                                        &conf->trusted_certificate,
                                        conf->verify_depth)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

        if (ngx_ssl_crl(cf, &conf->ssl, &conf->crl) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    if (ngx_ssl_ciphers(cf, &conf->ssl, &conf->ciphers,
                        conf->prefer_server_ciphers)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_dhparam(cf, &conf->ssl, &conf->dhparam) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_ecdh_curve(cf, &conf->ssl, &conf->ecdh_curve) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->builtin_session_cache,
                         prev->builtin_session_cache, NGX_SSL_NONE_SCACHE);

    if (conf->shm_zone == NULL) {
        conf->shm_zone = prev->shm_zone;
    }

    if (ngx_ssl_session_cache(&conf->ssl, &ngx_mail_ssl_sess_id_ctx,
                              conf->certificates, conf->builtin_session_cache,
                              conf->shm_zone, conf->session_timeout)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->session_tickets,
                         prev->session_tickets, 1);

#ifdef SSL_OP_NO_TICKET
    if (!conf->session_tickets) {
        SSL_CTX_set_options(conf->ssl.ctx, SSL_OP_NO_TICKET);
    }
#endif

    ngx_conf_merge_ptr_value(conf->session_ticket_keys,
                         prev->session_ticket_keys, NULL);

    if (ngx_ssl_session_ticket_keys(cf, &conf->ssl, conf->session_ticket_keys)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}