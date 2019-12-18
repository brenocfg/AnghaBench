#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int len; struct TYPE_26__* data; } ;
typedef  TYPE_3__ u_char ;
typedef  void* time_t ;
struct TYPE_27__ {int listen; int default_port; int backlog; int rcvbuf; int sndbuf; int setfib; int fastopen; int ipv6only; int default_server; int set; int bind; char* accept_filter; int deferred_accept; int reuseport; int ssl; int http2; int so_keepalive; int tcp_keepcnt; int proxy_protocol; size_t naddrs; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  wildcard; TYPE_2__* addrs; int /*<<< orphan*/  addr_text; int /*<<< orphan*/  socklen; void* tcp_keepintvl; void* tcp_keepidle; TYPE_3__ url; scalar_t__ err; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  TYPE_3__ ngx_str_t ;
typedef  TYPE_4__ ngx_http_listen_opt_t ;
struct TYPE_28__ {int listen; } ;
typedef  TYPE_7__ ngx_http_core_srv_conf_t ;
struct TYPE_29__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_25__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_24__ {size_t nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_ERROR ; 
 int NGX_LISTEN_BACKLOG ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 void* ngx_atoi (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_http_add_listen (TYPE_8__*,TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_inet_wildcard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 void* ngx_parse_size (TYPE_3__*) ; 
 void* ngx_parse_time (TYPE_3__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ngx_strcmp (TYPE_3__*,char*) ; 
 TYPE_3__* ngx_strlchr (TYPE_3__*,TYPE_3__*,char) ; 
 scalar_t__ ngx_strncmp (TYPE_3__*,char*,int) ; 

__attribute__((used)) static char *
ngx_http_core_listen(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_srv_conf_t *cscf = conf;

    ngx_str_t              *value, size;
    ngx_url_t               u;
    ngx_uint_t              n;
    ngx_http_listen_opt_t   lsopt;

    cscf->listen = 1;

    value = cf->args->elts;

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url = value[1];
    u.listen = 1;
    u.default_port = 80;

    if (ngx_parse_url(cf->pool, &u) != NGX_OK) {
        if (u.err) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "%s in \"%V\" of the \"listen\" directive",
                               u.err, &u.url);
        }

        return NGX_CONF_ERROR;
    }

    ngx_memzero(&lsopt, sizeof(ngx_http_listen_opt_t));

    lsopt.backlog = NGX_LISTEN_BACKLOG;
    lsopt.rcvbuf = -1;
    lsopt.sndbuf = -1;
#if (NGX_HAVE_SETFIB)
    lsopt.setfib = -1;
#endif
#if (NGX_HAVE_TCP_FASTOPEN)
    lsopt.fastopen = -1;
#endif
#if (NGX_HAVE_INET6)
    lsopt.ipv6only = 1;
#endif

    for (n = 2; n < cf->args->nelts; n++) {

        if (ngx_strcmp(value[n].data, "default_server") == 0
            || ngx_strcmp(value[n].data, "default") == 0)
        {
            lsopt.default_server = 1;
            continue;
        }

        if (ngx_strcmp(value[n].data, "bind") == 0) {
            lsopt.set = 1;
            lsopt.bind = 1;
            continue;
        }

#if (NGX_HAVE_SETFIB)
        if (ngx_strncmp(value[n].data, "setfib=", 7) == 0) {
            lsopt.setfib = ngx_atoi(value[n].data + 7, value[n].len - 7);
            lsopt.set = 1;
            lsopt.bind = 1;

            if (lsopt.setfib == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid setfib \"%V\"", &value[n]);
                return NGX_CONF_ERROR;
            }

            continue;
        }
#endif

#if (NGX_HAVE_TCP_FASTOPEN)
        if (ngx_strncmp(value[n].data, "fastopen=", 9) == 0) {
            lsopt.fastopen = ngx_atoi(value[n].data + 9, value[n].len - 9);
            lsopt.set = 1;
            lsopt.bind = 1;

            if (lsopt.fastopen == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid fastopen \"%V\"", &value[n]);
                return NGX_CONF_ERROR;
            }

            continue;
        }
#endif

        if (ngx_strncmp(value[n].data, "backlog=", 8) == 0) {
            lsopt.backlog = ngx_atoi(value[n].data + 8, value[n].len - 8);
            lsopt.set = 1;
            lsopt.bind = 1;

            if (lsopt.backlog == NGX_ERROR || lsopt.backlog == 0) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid backlog \"%V\"", &value[n]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[n].data, "rcvbuf=", 7) == 0) {
            size.len = value[n].len - 7;
            size.data = value[n].data + 7;

            lsopt.rcvbuf = ngx_parse_size(&size);
            lsopt.set = 1;
            lsopt.bind = 1;

            if (lsopt.rcvbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid rcvbuf \"%V\"", &value[n]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[n].data, "sndbuf=", 7) == 0) {
            size.len = value[n].len - 7;
            size.data = value[n].data + 7;

            lsopt.sndbuf = ngx_parse_size(&size);
            lsopt.set = 1;
            lsopt.bind = 1;

            if (lsopt.sndbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid sndbuf \"%V\"", &value[n]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[n].data, "accept_filter=", 14) == 0) {
#if (NGX_HAVE_DEFERRED_ACCEPT && defined SO_ACCEPTFILTER)
            lsopt.accept_filter = (char *) &value[n].data[14];
            lsopt.set = 1;
            lsopt.bind = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "accept filters \"%V\" are not supported "
                               "on this platform, ignored",
                               &value[n]);
#endif
            continue;
        }

        if (ngx_strcmp(value[n].data, "deferred") == 0) {
#if (NGX_HAVE_DEFERRED_ACCEPT && defined TCP_DEFER_ACCEPT)
            lsopt.deferred_accept = 1;
            lsopt.set = 1;
            lsopt.bind = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the deferred accept is not supported "
                               "on this platform, ignored");
#endif
            continue;
        }

        if (ngx_strncmp(value[n].data, "ipv6only=o", 10) == 0) {
#if (NGX_HAVE_INET6 && defined IPV6_V6ONLY)
            if (ngx_strcmp(&value[n].data[10], "n") == 0) {
                lsopt.ipv6only = 1;

            } else if (ngx_strcmp(&value[n].data[10], "ff") == 0) {
                lsopt.ipv6only = 0;

            } else {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid ipv6only flags \"%s\"",
                                   &value[n].data[9]);
                return NGX_CONF_ERROR;
            }

            lsopt.set = 1;
            lsopt.bind = 1;

            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "ipv6only is not supported "
                               "on this platform");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[n].data, "reuseport") == 0) {
#if (NGX_HAVE_REUSEPORT)
            lsopt.reuseport = 1;
            lsopt.set = 1;
            lsopt.bind = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "reuseport is not supported "
                               "on this platform, ignored");
#endif
            continue;
        }

        if (ngx_strcmp(value[n].data, "ssl") == 0) {
#if (NGX_HTTP_SSL)
            lsopt.ssl = 1;
            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the \"ssl\" parameter requires "
                               "ngx_http_ssl_module");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[n].data, "http2") == 0) {
#if (NGX_HTTP_V2)
            lsopt.http2 = 1;
            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the \"http2\" parameter requires "
                               "ngx_http_v2_module");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[n].data, "spdy") == 0) {
            ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                               "invalid parameter \"spdy\": "
                               "ngx_http_spdy_module was superseded "
                               "by ngx_http_v2_module");
            continue;
        }

        if (ngx_strncmp(value[n].data, "so_keepalive=", 13) == 0) {

            if (ngx_strcmp(&value[n].data[13], "on") == 0) {
                lsopt.so_keepalive = 1;

            } else if (ngx_strcmp(&value[n].data[13], "off") == 0) {
                lsopt.so_keepalive = 2;

            } else {

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
                u_char     *p, *end;
                ngx_str_t   s;

                end = value[n].data + value[n].len;
                s.data = value[n].data + 13;

                p = ngx_strlchr(s.data, end, ':');
                if (p == NULL) {
                    p = end;
                }

                if (p > s.data) {
                    s.len = p - s.data;

                    lsopt.tcp_keepidle = ngx_parse_time(&s, 1);
                    if (lsopt.tcp_keepidle == (time_t) NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                s.data = (p < end) ? (p + 1) : end;

                p = ngx_strlchr(s.data, end, ':');
                if (p == NULL) {
                    p = end;
                }

                if (p > s.data) {
                    s.len = p - s.data;

                    lsopt.tcp_keepintvl = ngx_parse_time(&s, 1);
                    if (lsopt.tcp_keepintvl == (time_t) NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                s.data = (p < end) ? (p + 1) : end;

                if (s.data < end) {
                    s.len = end - s.data;

                    lsopt.tcp_keepcnt = ngx_atoi(s.data, s.len);
                    if (lsopt.tcp_keepcnt == NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                if (lsopt.tcp_keepidle == 0 && lsopt.tcp_keepintvl == 0
                    && lsopt.tcp_keepcnt == 0)
                {
                    goto invalid_so_keepalive;
                }

                lsopt.so_keepalive = 1;

#else

                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "the \"so_keepalive\" parameter accepts "
                                   "only \"on\" or \"off\" on this platform");
                return NGX_CONF_ERROR;

#endif
            }

            lsopt.set = 1;
            lsopt.bind = 1;

            continue;

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
        invalid_so_keepalive:

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid so_keepalive value: \"%s\"",
                               &value[n].data[13]);
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[n].data, "proxy_protocol") == 0) {
            lsopt.proxy_protocol = 1;
            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[n]);
        return NGX_CONF_ERROR;
    }

    for (n = 0; n < u.naddrs; n++) {
        lsopt.sockaddr = u.addrs[n].sockaddr;
        lsopt.socklen = u.addrs[n].socklen;
        lsopt.addr_text = u.addrs[n].name;
        lsopt.wildcard = ngx_inet_wildcard(lsopt.sockaddr);

        if (ngx_http_add_listen(cf, cscf, &lsopt) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}