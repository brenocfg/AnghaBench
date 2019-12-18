#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_35__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_13__ ;
typedef  struct TYPE_37__   TYPE_12__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
struct TYPE_51__ {int len; struct TYPE_51__* data; } ;
typedef  TYPE_9__ u_char ;
typedef  void* time_t ;
struct TYPE_36__ {int listen; size_t naddrs; scalar_t__ backlog; int rcvbuf; int sndbuf; int ipv6only; scalar_t__ port; int bind; int ssl; int so_keepalive; scalar_t__ tcp_keepcnt; TYPE_9__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  wildcard; TYPE_8__* addrs; void* tcp_keepintvl; void* tcp_keepidle; int /*<<< orphan*/  ctx; TYPE_9__ url; scalar_t__ err; } ;
typedef  TYPE_10__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  TYPE_9__ ngx_str_t ;
struct TYPE_37__ {int listen; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  TYPE_12__ ngx_mail_ssl_conf_t ;
struct TYPE_38__ {TYPE_3__* protocol; } ;
typedef  TYPE_13__ ngx_mail_module_t ;
typedef  TYPE_10__ ngx_mail_listen_t ;
struct TYPE_39__ {int listen; TYPE_3__* protocol; } ;
typedef  TYPE_15__ ngx_mail_core_srv_conf_t ;
struct TYPE_44__ {size_t nelts; TYPE_10__* elts; } ;
struct TYPE_40__ {TYPE_35__ listen; } ;
typedef  TYPE_16__ ngx_mail_core_main_conf_t ;
struct TYPE_41__ {TYPE_7__* conf_file; TYPE_4__* args; TYPE_2__* cycle; int /*<<< orphan*/  ctx; int /*<<< orphan*/  pool; } ;
typedef  TYPE_17__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_50__ {TYPE_9__ name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_47__ {int /*<<< orphan*/  data; } ;
struct TYPE_48__ {TYPE_5__ name; } ;
struct TYPE_49__ {int /*<<< orphan*/  line; TYPE_6__ file; } ;
struct TYPE_46__ {size_t nelts; TYPE_9__* elts; } ;
struct TYPE_45__ {scalar_t__* port; } ;
struct TYPE_43__ {TYPE_1__** modules; } ;
struct TYPE_42__ {scalar_t__ type; TYPE_13__* ctx; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_LISTEN_BACKLOG ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_MAIL_MODULE ; 
 scalar_t__ NGX_OK ; 
 TYPE_10__* ngx_array_push_n (TYPE_35__*,size_t) ; 
 void* ngx_atoi (TYPE_9__*,int) ; 
 scalar_t__ ngx_cmp_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_inet_wildcard (int /*<<< orphan*/ ) ; 
 TYPE_16__* ngx_mail_conf_get_module_main_conf (TYPE_17__*,int /*<<< orphan*/ ) ; 
 TYPE_12__* ngx_mail_conf_get_module_srv_conf (TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_10__*,int) ; 
 void* ngx_parse_size (TYPE_9__*) ; 
 void* ngx_parse_time (TYPE_9__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ ngx_strcmp (TYPE_9__*,char*) ; 
 TYPE_9__* ngx_strlchr (TYPE_9__*,TYPE_9__*,char) ; 
 scalar_t__ ngx_strncmp (TYPE_9__*,char*,int) ; 

__attribute__((used)) static char *
ngx_mail_core_listen(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_mail_core_srv_conf_t  *cscf = conf;

    ngx_str_t                  *value, size;
    ngx_url_t                   u;
    ngx_uint_t                  i, n, m;
    ngx_mail_listen_t          *ls, *als;
    ngx_mail_module_t          *module;
    ngx_mail_core_main_conf_t  *cmcf;

    cscf->listen = 1;

    value = cf->args->elts;

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url = value[1];
    u.listen = 1;

    if (ngx_parse_url(cf->pool, &u) != NGX_OK) {
        if (u.err) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "%s in \"%V\" of the \"listen\" directive",
                               u.err, &u.url);
        }

        return NGX_CONF_ERROR;
    }

    cmcf = ngx_mail_conf_get_module_main_conf(cf, ngx_mail_core_module);

    ls = ngx_array_push_n(&cmcf->listen, u.naddrs);
    if (ls == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(ls, sizeof(ngx_mail_listen_t));

    ls->backlog = NGX_LISTEN_BACKLOG;
    ls->rcvbuf = -1;
    ls->sndbuf = -1;
    ls->ctx = cf->ctx;

#if (NGX_HAVE_INET6)
    ls->ipv6only = 1;
#endif

    if (cscf->protocol == NULL) {
        for (m = 0; cf->cycle->modules[m]; m++) {
            if (cf->cycle->modules[m]->type != NGX_MAIL_MODULE) {
                continue;
            }

            module = cf->cycle->modules[m]->ctx;

            if (module->protocol == NULL) {
                continue;
            }

            for (i = 0; module->protocol->port[i]; i++) {
                if (module->protocol->port[i] == u.port) {
                    cscf->protocol = module->protocol;
                    break;
                }
            }
        }
    }

    for (i = 2; i < cf->args->nelts; i++) {

        if (ngx_strcmp(value[i].data, "bind") == 0) {
            ls->bind = 1;
            continue;
        }

        if (ngx_strncmp(value[i].data, "backlog=", 8) == 0) {
            ls->backlog = ngx_atoi(value[i].data + 8, value[i].len - 8);
            ls->bind = 1;

            if (ls->backlog == NGX_ERROR || ls->backlog == 0) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid backlog \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "rcvbuf=", 7) == 0) {
            size.len = value[i].len - 7;
            size.data = value[i].data + 7;

            ls->rcvbuf = ngx_parse_size(&size);
            ls->bind = 1;

            if (ls->rcvbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid rcvbuf \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "sndbuf=", 7) == 0) {
            size.len = value[i].len - 7;
            size.data = value[i].data + 7;

            ls->sndbuf = ngx_parse_size(&size);
            ls->bind = 1;

            if (ls->sndbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid sndbuf \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "ipv6only=o", 10) == 0) {
#if (NGX_HAVE_INET6 && defined IPV6_V6ONLY)
            if (ngx_strcmp(&value[i].data[10], "n") == 0) {
                ls->ipv6only = 1;

            } else if (ngx_strcmp(&value[i].data[10], "ff") == 0) {
                ls->ipv6only = 0;

            } else {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid ipv6only flags \"%s\"",
                                   &value[i].data[9]);
                return NGX_CONF_ERROR;
            }

            ls->bind = 1;
            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "bind ipv6only is not supported "
                               "on this platform");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[i].data, "ssl") == 0) {
#if (NGX_MAIL_SSL)
            ngx_mail_ssl_conf_t  *sslcf;

            sslcf = ngx_mail_conf_get_module_srv_conf(cf, ngx_mail_ssl_module);

            sslcf->listen = 1;
            sslcf->file = cf->conf_file->file.name.data;
            sslcf->line = cf->conf_file->line;

            ls->ssl = 1;

            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the \"ssl\" parameter requires "
                               "ngx_mail_ssl_module");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strncmp(value[i].data, "so_keepalive=", 13) == 0) {

            if (ngx_strcmp(&value[i].data[13], "on") == 0) {
                ls->so_keepalive = 1;

            } else if (ngx_strcmp(&value[i].data[13], "off") == 0) {
                ls->so_keepalive = 2;

            } else {

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
                u_char     *p, *end;
                ngx_str_t   s;

                end = value[i].data + value[i].len;
                s.data = value[i].data + 13;

                p = ngx_strlchr(s.data, end, ':');
                if (p == NULL) {
                    p = end;
                }

                if (p > s.data) {
                    s.len = p - s.data;

                    ls->tcp_keepidle = ngx_parse_time(&s, 1);
                    if (ls->tcp_keepidle == (time_t) NGX_ERROR) {
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

                    ls->tcp_keepintvl = ngx_parse_time(&s, 1);
                    if (ls->tcp_keepintvl == (time_t) NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                s.data = (p < end) ? (p + 1) : end;

                if (s.data < end) {
                    s.len = end - s.data;

                    ls->tcp_keepcnt = ngx_atoi(s.data, s.len);
                    if (ls->tcp_keepcnt == NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                if (ls->tcp_keepidle == 0 && ls->tcp_keepintvl == 0
                    && ls->tcp_keepcnt == 0)
                {
                    goto invalid_so_keepalive;
                }

                ls->so_keepalive = 1;

#else

                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "the \"so_keepalive\" parameter accepts "
                                   "only \"on\" or \"off\" on this platform");
                return NGX_CONF_ERROR;

#endif
            }

            ls->bind = 1;

            continue;

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
        invalid_so_keepalive:

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid so_keepalive value: \"%s\"",
                               &value[i].data[13]);
            return NGX_CONF_ERROR;
#endif
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "the invalid \"%V\" parameter", &value[i]);
        return NGX_CONF_ERROR;
    }

    als = cmcf->listen.elts;

    for (n = 0; n < u.naddrs; n++) {
        ls[n] = ls[0];

        ls[n].sockaddr = u.addrs[n].sockaddr;
        ls[n].socklen = u.addrs[n].socklen;
        ls[n].addr_text = u.addrs[n].name;
        ls[n].wildcard = ngx_inet_wildcard(ls[n].sockaddr);

        for (i = 0; i < cmcf->listen.nelts - u.naddrs + n; i++) {

            if (ngx_cmp_sockaddr(als[i].sockaddr, als[i].socklen,
                                 ls[n].sockaddr, ls[n].socklen, 1)
                != NGX_OK)
            {
                continue;
            }

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "duplicate \"%V\" address and port pair",
                               &ls[n].addr_text);
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}