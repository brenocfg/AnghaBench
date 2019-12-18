#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  ipv6only; int /*<<< orphan*/  tcp_keepcnt; int /*<<< orphan*/  tcp_keepintvl; int /*<<< orphan*/  tcp_keepidle; int /*<<< orphan*/  proxy_protocol; int /*<<< orphan*/  so_keepalive; int /*<<< orphan*/  wildcard; int /*<<< orphan*/  bind; int /*<<< orphan*/  ctx; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_1__ ngx_rtmp_listen_t ;
struct TYPE_15__ {size_t nelts; TYPE_2__* elts; } ;
struct TYPE_12__ {int family; TYPE_5__ addrs; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ ngx_rtmp_conf_port_t ;
struct TYPE_13__ {int /*<<< orphan*/  ipv6only; int /*<<< orphan*/  tcp_keepcnt; int /*<<< orphan*/  tcp_keepintvl; int /*<<< orphan*/  tcp_keepidle; int /*<<< orphan*/  proxy_protocol; int /*<<< orphan*/  so_keepalive; int /*<<< orphan*/  wildcard; int /*<<< orphan*/  bind; int /*<<< orphan*/  ctx; int /*<<< orphan*/  socklen; struct sockaddr* sockaddr; } ;
typedef  TYPE_3__ ngx_rtmp_conf_addr_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  TYPE_5__ ngx_array_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
#define  AF_INET6 128 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 
 void* ngx_array_push (TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_add_ports(ngx_conf_t *cf, ngx_array_t *ports,
    ngx_rtmp_listen_t *listen)
{
    in_port_t              p;
    ngx_uint_t             i;
    struct sockaddr       *sa;
    struct sockaddr_in    *sin;
    ngx_rtmp_conf_port_t  *port;
    ngx_rtmp_conf_addr_t  *addr;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6   *sin6;
#endif

    sa = (struct sockaddr *) &listen->sockaddr;

    switch (sa->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) sa;
        p = sin6->sin6_port;
        break;
#endif

    default: /* AF_INET */
        sin = (struct sockaddr_in *) sa;
        p = sin->sin_port;
        break;
    }

    port = ports->elts;
    for (i = 0; i < ports->nelts; i++) {
        if (p == port[i].port && sa->sa_family == port[i].family) {

            /* a port is already in the port list */

            port = &port[i];
            goto found;
        }
    }

    /* add a port to the port list */

    port = ngx_array_push(ports);
    if (port == NULL) {
        return NGX_ERROR;
    }

    port->family = sa->sa_family;
    port->port = p;

    if (ngx_array_init(&port->addrs, cf->temp_pool, 2,
                       sizeof(ngx_rtmp_conf_addr_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

found:

    addr = ngx_array_push(&port->addrs);
    if (addr == NULL) {
        return NGX_ERROR;
    }

    addr->sockaddr = (struct sockaddr *) &listen->sockaddr;
    addr->socklen = listen->socklen;
    addr->ctx = listen->ctx;
    addr->bind = listen->bind;
    addr->wildcard = listen->wildcard;
    addr->so_keepalive = listen->so_keepalive;
    addr->proxy_protocol = listen->proxy_protocol;
#if (NGX_HAVE_KEEPALIVE_TUNABLE)
    addr->tcp_keepidle = listen->tcp_keepidle;
    addr->tcp_keepintvl = listen->tcp_keepintvl;
    addr->tcp_keepcnt = listen->tcp_keepcnt;
#endif
#if (NGX_HAVE_INET6 && defined IPV6_V6ONLY)
    addr->ipv6only = listen->ipv6only;
#endif

    return NGX_OK;
}