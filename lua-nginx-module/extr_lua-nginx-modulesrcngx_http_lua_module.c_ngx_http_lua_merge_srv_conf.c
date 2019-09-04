#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 

__attribute__((used)) static char *
ngx_http_lua_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
#if (NGX_HTTP_SSL)

    ngx_http_lua_srv_conf_t *prev = parent;
    ngx_http_lua_srv_conf_t *conf = child;
    ngx_http_ssl_srv_conf_t *sscf;

    dd("merge srv conf");

    if (conf->srv.ssl_cert_src.len == 0) {
        conf->srv.ssl_cert_src = prev->srv.ssl_cert_src;
        conf->srv.ssl_cert_src_key = prev->srv.ssl_cert_src_key;
        conf->srv.ssl_cert_handler = prev->srv.ssl_cert_handler;
    }

    if (conf->srv.ssl_cert_src.len) {
        sscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_ssl_module);
        if (sscf == NULL || sscf->ssl.ctx == NULL) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no ssl configured for the server");

            return NGX_CONF_ERROR;
        }

#ifdef LIBRESSL_VERSION_NUMBER

        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "LibreSSL does not support ssl_certificate_by_lua*");
        return NGX_CONF_ERROR;

#else

#   if OPENSSL_VERSION_NUMBER >= 0x1000205fL

        SSL_CTX_set_cert_cb(sscf->ssl.ctx, ngx_http_lua_ssl_cert_handler, NULL);

#   else

        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "OpenSSL too old to support ssl_certificate_by_lua*");
        return NGX_CONF_ERROR;

#   endif

#endif
    }

    if (conf->srv.ssl_sess_store_src.len == 0) {
        conf->srv.ssl_sess_store_src = prev->srv.ssl_sess_store_src;
        conf->srv.ssl_sess_store_src_key = prev->srv.ssl_sess_store_src_key;
        conf->srv.ssl_sess_store_handler = prev->srv.ssl_sess_store_handler;
    }

    if (conf->srv.ssl_sess_store_src.len) {
        sscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_ssl_module);
        if (sscf && sscf->ssl.ctx) {
#ifdef LIBRESSL_VERSION_NUMBER
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "LibreSSL does not support "
                          "ssl_session_store_by_lua*");

            return NGX_CONF_ERROR;
#else
            SSL_CTX_sess_set_new_cb(sscf->ssl.ctx,
                                    ngx_http_lua_ssl_sess_store_handler);
#endif
        }
    }

    if (conf->srv.ssl_sess_fetch_src.len == 0) {
        conf->srv.ssl_sess_fetch_src = prev->srv.ssl_sess_fetch_src;
        conf->srv.ssl_sess_fetch_src_key = prev->srv.ssl_sess_fetch_src_key;
        conf->srv.ssl_sess_fetch_handler = prev->srv.ssl_sess_fetch_handler;
    }

    if (conf->srv.ssl_sess_fetch_src.len) {
        sscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_ssl_module);
        if (sscf && sscf->ssl.ctx) {
#ifdef LIBRESSL_VERSION_NUMBER
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "LibreSSL does not support "
                          "ssl_session_fetch_by_lua*");

            return NGX_CONF_ERROR;
#else
            SSL_CTX_sess_set_get_cb(sscf->ssl.ctx,
                                    ngx_http_lua_ssl_sess_fetch_handler);
#endif
        }
    }

#endif  /* NGX_HTTP_SSL */
    return NGX_CONF_OK;
}