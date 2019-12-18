#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_28__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int ngx_uint_t ;
struct TYPE_30__ {int /*<<< orphan*/  ssl; scalar_t__ enable; } ;
typedef  TYPE_4__ ngx_mail_ssl_conf_t ;
struct TYPE_31__ {int /*<<< orphan*/ * addr_text; TYPE_12__* connection; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; int /*<<< orphan*/  signature; } ;
typedef  TYPE_5__ ngx_mail_session_t ;
struct TYPE_32__ {int naddrs; TYPE_8__* addrs; } ;
typedef  TYPE_6__ ngx_mail_port_t ;
struct TYPE_33__ {TYPE_5__* session; int /*<<< orphan*/ * client; } ;
typedef  TYPE_7__ ngx_mail_log_ctx_t ;
struct TYPE_24__ {scalar_t__ ssl; int /*<<< orphan*/  addr_text; TYPE_3__* ctx; } ;
struct TYPE_34__ {TYPE_11__ conf; int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
typedef  TYPE_8__ ngx_mail_in_addr_t ;
typedef  TYPE_8__ ngx_mail_in6_addr_t ;
struct TYPE_23__ {int /*<<< orphan*/  error_log; } ;
typedef  TYPE_10__ ngx_mail_core_srv_conf_t ;
typedef  TYPE_11__ ngx_mail_addr_conf_t ;
struct TYPE_25__ {TYPE_21__* log; int /*<<< orphan*/  log_error; int /*<<< orphan*/  number; int /*<<< orphan*/  addr_text; int /*<<< orphan*/  pool; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_5__* data; struct sockaddr* local_sockaddr; TYPE_1__* listening; } ;
typedef  TYPE_12__ ngx_connection_t ;
struct TYPE_29__ {int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
struct TYPE_27__ {char* action; TYPE_7__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  connection; } ;
struct TYPE_26__ {TYPE_6__* servers; } ;

/* Variables and functions */
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_ERROR_INFO ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_MAIL_MODULE ; 
 scalar_t__ NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 scalar_t__ ngx_connection_local_sockaddr (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_21__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 void* ngx_mail_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_init_session (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_mail_log_error ; 
 int /*<<< orphan*/  ngx_mail_ssl_init_connection (int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 
 int /*<<< orphan*/  ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_7__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_set_connection_log (TYPE_12__*,int /*<<< orphan*/ ) ; 
 size_t ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void
ngx_mail_init_connection(ngx_connection_t *c)
{
    size_t                     len;
    ngx_uint_t                 i;
    ngx_mail_port_t           *port;
    struct sockaddr           *sa;
    struct sockaddr_in        *sin;
    ngx_mail_log_ctx_t        *ctx;
    ngx_mail_in_addr_t        *addr;
    ngx_mail_session_t        *s;
    ngx_mail_addr_conf_t      *addr_conf;
    ngx_mail_core_srv_conf_t  *cscf;
    u_char                     text[NGX_SOCKADDR_STRLEN];
#if (NGX_HAVE_INET6)
    struct sockaddr_in6       *sin6;
    ngx_mail_in6_addr_t       *addr6;
#endif


    /* find the server configuration for the address:port */

    port = c->listening->servers;

    if (port->naddrs > 1) {

        /*
         * There are several addresses on this port and one of them
         * is the "*:port" wildcard so getsockname() is needed to determine
         * the server address.
         *
         * AcceptEx() already gave this address.
         */

        if (ngx_connection_local_sockaddr(c, NULL, 0) != NGX_OK) {
            ngx_mail_close_connection(c);
            return;
        }

        sa = c->local_sockaddr;

        switch (sa->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            sin6 = (struct sockaddr_in6 *) sa;

            addr6 = port->addrs;

            /* the last address is "*" */

            for (i = 0; i < port->naddrs - 1; i++) {
                if (ngx_memcmp(&addr6[i].addr6, &sin6->sin6_addr, 16) == 0) {
                    break;
                }
            }

            addr_conf = &addr6[i].conf;

            break;
#endif

        default: /* AF_INET */
            sin = (struct sockaddr_in *) sa;

            addr = port->addrs;

            /* the last address is "*" */

            for (i = 0; i < port->naddrs - 1; i++) {
                if (addr[i].addr == sin->sin_addr.s_addr) {
                    break;
                }
            }

            addr_conf = &addr[i].conf;

            break;
        }

    } else {
        switch (c->local_sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            addr6 = port->addrs;
            addr_conf = &addr6[0].conf;
            break;
#endif

        default: /* AF_INET */
            addr = port->addrs;
            addr_conf = &addr[0].conf;
            break;
        }
    }

    s = ngx_pcalloc(c->pool, sizeof(ngx_mail_session_t));
    if (s == NULL) {
        ngx_mail_close_connection(c);
        return;
    }

    s->signature = NGX_MAIL_MODULE;

    s->main_conf = addr_conf->ctx->main_conf;
    s->srv_conf = addr_conf->ctx->srv_conf;

    s->addr_text = &addr_conf->addr_text;

    c->data = s;
    s->connection = c;

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    ngx_set_connection_log(c, cscf->error_log);

    len = ngx_sock_ntop(c->sockaddr, c->socklen, text, NGX_SOCKADDR_STRLEN, 1);

    ngx_log_error(NGX_LOG_INFO, c->log, 0, "*%uA client %*s connected to %V",
                  c->number, len, text, s->addr_text);

    ctx = ngx_palloc(c->pool, sizeof(ngx_mail_log_ctx_t));
    if (ctx == NULL) {
        ngx_mail_close_connection(c);
        return;
    }

    ctx->client = &c->addr_text;
    ctx->session = s;

    c->log->connection = c->number;
    c->log->handler = ngx_mail_log_error;
    c->log->data = ctx;
    c->log->action = "sending client greeting line";

    c->log_error = NGX_ERROR_INFO;

#if (NGX_MAIL_SSL)
    {
    ngx_mail_ssl_conf_t  *sslcf;

    sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);

    if (sslcf->enable || addr_conf->ssl) {
        c->log->action = "SSL handshaking";

        ngx_mail_ssl_init_connection(&sslcf->ssl, c);
        return;
    }

    }
#endif

    ngx_mail_init_session(c);
}