#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_19__ {int /*<<< orphan*/  addr_text; scalar_t__ ssl; scalar_t__ http2; } ;
typedef  TYPE_3__ ngx_http_listen_opt_t ;
typedef  int /*<<< orphan*/  ngx_http_core_srv_conf_t ;
struct TYPE_16__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_20__ {TYPE_14__ addrs; } ;
typedef  TYPE_4__ ngx_http_conf_port_t ;
struct TYPE_18__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/ * buckets; } ;
struct TYPE_21__ {TYPE_2__ servers; int /*<<< orphan*/ * default_server; int /*<<< orphan*/ * regex; scalar_t__ nregex; int /*<<< orphan*/ * wc_tail; int /*<<< orphan*/ * wc_head; TYPE_1__ hash; TYPE_3__ opt; } ;
typedef  TYPE_5__ ngx_http_conf_addr_t ;
struct TYPE_22__ {int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_6__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_14__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (TYPE_14__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_add_server (TYPE_6__*,int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_add_address(ngx_conf_t *cf, ngx_http_core_srv_conf_t *cscf,
    ngx_http_conf_port_t *port, ngx_http_listen_opt_t *lsopt)
{
    ngx_http_conf_addr_t  *addr;

    if (port->addrs.elts == NULL) {
        if (ngx_array_init(&port->addrs, cf->temp_pool, 4,
                           sizeof(ngx_http_conf_addr_t))
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

#if (NGX_HTTP_V2 && NGX_HTTP_SSL                                              \
     && !defined TLSEXT_TYPE_application_layer_protocol_negotiation           \
     && !defined TLSEXT_TYPE_next_proto_neg)

    if (lsopt->http2 && lsopt->ssl) {
        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                           "nginx was built with OpenSSL that lacks ALPN "
                           "and NPN support, HTTP/2 is not enabled for %V",
                           &lsopt->addr_text);
    }

#endif

    addr = ngx_array_push(&port->addrs);
    if (addr == NULL) {
        return NGX_ERROR;
    }

    addr->opt = *lsopt;
    addr->hash.buckets = NULL;
    addr->hash.size = 0;
    addr->wc_head = NULL;
    addr->wc_tail = NULL;
#if (NGX_PCRE)
    addr->nregex = 0;
    addr->regex = NULL;
#endif
    addr->default_server = cscf;
    addr->servers.elts = NULL;

    return ngx_http_add_server(cf, cscf, addr);
}