#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int ngx_uint_t ;
struct TYPE_19__ {int auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_20__ {int naddrs; TYPE_5__* addrs; } ;
typedef  TYPE_4__ ngx_rtmp_port_t ;
struct TYPE_22__ {scalar_t__ proxy_protocol; } ;
struct TYPE_21__ {TYPE_7__ conf; int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
typedef  TYPE_5__ ngx_rtmp_in_addr_t ;
typedef  TYPE_5__ ngx_rtmp_in6_addr_t ;
typedef  TYPE_7__ ngx_rtmp_addr_conf_t ;
typedef  int ngx_int_t ;
struct TYPE_23__ {int /*<<< orphan*/  addr_text; int /*<<< orphan*/  number; int /*<<< orphan*/  log; struct sockaddr* local_sockaddr; TYPE_1__* listening; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_17__ {TYPE_4__* servers; } ;

/* Variables and functions */
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_connection_local_sockaddr (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_close_connection (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake (TYPE_3__*) ; 
 TYPE_3__* ngx_rtmp_init_session (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_rtmp_naccepted ; 
 int /*<<< orphan*/  ngx_rtmp_proxy_protocol (TYPE_3__*) ; 

void
ngx_rtmp_init_connection(ngx_connection_t *c)
{
    ngx_uint_t             i;
    ngx_rtmp_port_t       *port;
    struct sockaddr       *sa;
    struct sockaddr_in    *sin;
    ngx_rtmp_in_addr_t    *addr;
    ngx_rtmp_session_t    *s;
    ngx_rtmp_addr_conf_t  *addr_conf;
    ngx_int_t              unix_socket;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6   *sin6;
    ngx_rtmp_in6_addr_t   *addr6;
#endif

    ++ngx_rtmp_naccepted;

    /* find the server configuration for the address:port */

    /* AF_INET only */

    port = c->listening->servers;
    unix_socket = 0;

    if (port->naddrs > 1) {

        /*
         * There are several addresses on this port and one of them
         * is the "*:port" wildcard so getsockname() is needed to determine
         * the server address.
         *
         * AcceptEx() already gave this address.
         */

        if (ngx_connection_local_sockaddr(c, NULL, 0) != NGX_OK) {
            ngx_rtmp_close_connection(c);
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

        case AF_UNIX:
            unix_socket = 1;
            /* fall through */

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

        case AF_UNIX:
            unix_socket = 1;
            /* fall through */

        default: /* AF_INET */
            addr = port->addrs;
            addr_conf = &addr[0].conf;
            break;
        }
    }

    ngx_log_error(NGX_LOG_INFO, c->log, 0, "*%ui client connected '%V'",
                  c->number, &c->addr_text);

    s = ngx_rtmp_init_session(c, addr_conf);
    if (s == NULL) {
        return;
    }

    /* only auto-pushed connections are
     * done through unix socket */

    s->auto_pushed = unix_socket;

    if (addr_conf->proxy_protocol) {
        ngx_rtmp_proxy_protocol(s);

    } else {
        ngx_rtmp_handshake(s);
    }
}