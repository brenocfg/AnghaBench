#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_29__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_15__ ;
typedef  struct TYPE_36__   TYPE_14__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_40__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int ngx_uint_t ;
struct TYPE_44__ {int /*<<< orphan*/  msec; int /*<<< orphan*/  sec; } ;
typedef  TYPE_6__ ngx_time_t ;
typedef  int /*<<< orphan*/  ngx_stream_variable_value_t ;
struct TYPE_45__ {int /*<<< orphan*/  start_msec; int /*<<< orphan*/  start_sec; int /*<<< orphan*/ * variables; TYPE_15__* connection; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  received; int /*<<< orphan*/  ssl; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; int /*<<< orphan*/  signature; } ;
typedef  TYPE_7__ ngx_stream_session_t ;
struct TYPE_46__ {int naddrs; TYPE_9__* addrs; } ;
typedef  TYPE_8__ ngx_stream_port_t ;
struct TYPE_35__ {scalar_t__ proxy_protocol; int /*<<< orphan*/  addr_text; int /*<<< orphan*/  ssl; TYPE_3__* ctx; } ;
struct TYPE_47__ {TYPE_13__ conf; int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
typedef  TYPE_9__ ngx_stream_in_addr_t ;
typedef  TYPE_9__ ngx_stream_in6_addr_t ;
struct TYPE_33__ {int /*<<< orphan*/  proxy_protocol_timeout; int /*<<< orphan*/  error_log; } ;
typedef  TYPE_11__ ngx_stream_core_srv_conf_t ;
struct TYPE_43__ {int nelts; } ;
struct TYPE_34__ {TYPE_5__ variables; } ;
typedef  TYPE_12__ ngx_stream_core_main_conf_t ;
typedef  TYPE_13__ ngx_stream_addr_conf_t ;
struct TYPE_36__ {int /*<<< orphan*/  (* handler ) (TYPE_14__*) ;int /*<<< orphan*/  ready; } ;
typedef  TYPE_14__ ngx_event_t ;
struct TYPE_37__ {scalar_t__ type; TYPE_29__* log; TYPE_14__* read; int /*<<< orphan*/  pool; int /*<<< orphan*/  log_error; int /*<<< orphan*/  number; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_7__* data; TYPE_4__* buffer; struct sockaddr* local_sockaddr; TYPE_1__* listening; } ;
typedef  TYPE_15__ ngx_connection_t ;
struct TYPE_42__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_41__ {int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
struct TYPE_39__ {char* action; TYPE_7__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  connection; } ;
struct TYPE_38__ {TYPE_8__* servers; } ;

/* Variables and functions */
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_ERROR_INFO ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_STREAM_MODULE ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_14__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_connection_local_sockaddr (TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_29__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_14__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_set_connection_log (TYPE_15__*,int /*<<< orphan*/ ) ; 
 size_t ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ngx_stream_close_connection (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 int /*<<< orphan*/  ngx_stream_finalize_session (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_12__* ngx_stream_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_11__* ngx_stream_get_module_srv_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_log_error ; 
 int ngx_stream_max_module ; 
 int /*<<< orphan*/  ngx_stream_proxy_protocol_handler (TYPE_14__*) ; 
 int /*<<< orphan*/  ngx_stream_session_handler (TYPE_14__*) ; 
 TYPE_6__* ngx_timeofday () ; 
 scalar_t__ ngx_use_accept_mutex ; 
 int /*<<< orphan*/  stub1 (TYPE_14__*) ; 

void
ngx_stream_init_connection(ngx_connection_t *c)
{
    u_char                        text[NGX_SOCKADDR_STRLEN];
    size_t                        len;
    ngx_uint_t                    i;
    ngx_time_t                   *tp;
    ngx_event_t                  *rev;
    struct sockaddr              *sa;
    ngx_stream_port_t            *port;
    struct sockaddr_in           *sin;
    ngx_stream_in_addr_t         *addr;
    ngx_stream_session_t         *s;
    ngx_stream_addr_conf_t       *addr_conf;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6          *sin6;
    ngx_stream_in6_addr_t        *addr6;
#endif
    ngx_stream_core_srv_conf_t   *cscf;
    ngx_stream_core_main_conf_t  *cmcf;

    /* find the server configuration for the address:port */

    port = c->listening->servers;

    if (port->naddrs > 1) {

        /*
         * There are several addresses on this port and one of them
         * is the "*:port" wildcard so getsockname() is needed to determine
         * the server address.
         *
         * AcceptEx() and recvmsg() already gave this address.
         */

        if (ngx_connection_local_sockaddr(c, NULL, 0) != NGX_OK) {
            ngx_stream_close_connection(c);
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

    s = ngx_pcalloc(c->pool, sizeof(ngx_stream_session_t));
    if (s == NULL) {
        ngx_stream_close_connection(c);
        return;
    }

    s->signature = NGX_STREAM_MODULE;
    s->main_conf = addr_conf->ctx->main_conf;
    s->srv_conf = addr_conf->ctx->srv_conf;

#if (NGX_STREAM_SSL)
    s->ssl = addr_conf->ssl;
#endif

    if (c->buffer) {
        s->received += c->buffer->last - c->buffer->pos;
    }

    s->connection = c;
    c->data = s;

    cscf = ngx_stream_get_module_srv_conf(s, ngx_stream_core_module);

    ngx_set_connection_log(c, cscf->error_log);

    len = ngx_sock_ntop(c->sockaddr, c->socklen, text, NGX_SOCKADDR_STRLEN, 1);

    ngx_log_error(NGX_LOG_INFO, c->log, 0, "*%uA %sclient %*s connected to %V",
                  c->number, c->type == SOCK_DGRAM ? "udp " : "",
                  len, text, &addr_conf->addr_text);

    c->log->connection = c->number;
    c->log->handler = ngx_stream_log_error;
    c->log->data = s;
    c->log->action = "initializing session";
    c->log_error = NGX_ERROR_INFO;

    s->ctx = ngx_pcalloc(c->pool, sizeof(void *) * ngx_stream_max_module);
    if (s->ctx == NULL) {
        ngx_stream_close_connection(c);
        return;
    }

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    s->variables = ngx_pcalloc(s->connection->pool,
                               cmcf->variables.nelts
                               * sizeof(ngx_stream_variable_value_t));

    if (s->variables == NULL) {
        ngx_stream_close_connection(c);
        return;
    }

    tp = ngx_timeofday();
    s->start_sec = tp->sec;
    s->start_msec = tp->msec;

    rev = c->read;
    rev->handler = ngx_stream_session_handler;

    if (addr_conf->proxy_protocol) {
        c->log->action = "reading PROXY protocol";

        rev->handler = ngx_stream_proxy_protocol_handler;

        if (!rev->ready) {
            ngx_add_timer(rev, cscf->proxy_protocol_timeout);

            if (ngx_handle_read_event(rev, 0) != NGX_OK) {
                ngx_stream_finalize_session(s,
                                            NGX_STREAM_INTERNAL_SERVER_ERROR);
            }

            return;
        }
    }

    if (ngx_use_accept_mutex) {
        ngx_post_event(rev, &ngx_posted_events);
        return;
    }

    rev->handler(rev);
}