#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_15__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; void* sin_port; void* sin_family; } ;
struct TYPE_21__ {int /*<<< orphan*/  sockaddr; } ;
struct TYPE_14__ {size_t len; char* data; } ;
struct TYPE_19__ {int len; char* data; } ;
struct TYPE_18__ {int len; char* data; } ;
struct TYPE_17__ {char* data; size_t len; } ;
struct TYPE_20__ {int socklen; char* err; int last_port; void* port; int wildcard; int no_port; void* default_port; TYPE_9__ sockaddr; TYPE_3__* addrs; void* family; scalar_t__ no_resolve; scalar_t__ listen; TYPE_1__ host; TYPE_6__ port_text; TYPE_5__ uri; int /*<<< orphan*/  uri_part; TYPE_4__ url; } ;
typedef  TYPE_7__ ngx_url_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int ngx_int_t ;
typedef  void* in_port_t ;
struct TYPE_16__ {int socklen; TYPE_10__* sockaddr; } ;
struct TYPE_13__ {void* sa_family; } ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 int NGX_ERROR ; 
 int NGX_OK ; 
 void* htons (void*) ; 
 int ngx_atoi (char*,size_t) ; 
 int ngx_inet_add_addr (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ngx_inet_addr (char*,size_t) ; 
 int ngx_inet_resolve_host (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int ngx_inet_wildcard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_9__*,TYPE_10__*,int) ; 
 char* ngx_strlchr (char*,char*,char) ; 

__attribute__((used)) static ngx_int_t
ngx_parse_inet_url(ngx_pool_t *pool, ngx_url_t *u)
{
    u_char              *host, *port, *last, *uri, *args, *dash;
    size_t               len;
    ngx_int_t            n;
    struct sockaddr_in  *sin;

    u->socklen = sizeof(struct sockaddr_in);
    sin = (struct sockaddr_in *) &u->sockaddr;
    sin->sin_family = AF_INET;

    u->family = AF_INET;

    host = u->url.data;

    last = host + u->url.len;

    port = ngx_strlchr(host, last, ':');

    uri = ngx_strlchr(host, last, '/');

    args = ngx_strlchr(host, last, '?');

    if (args) {
        if (uri == NULL || args < uri) {
            uri = args;
        }
    }

    if (uri) {
        if (u->listen || !u->uri_part) {
            u->err = "invalid host";
            return NGX_ERROR;
        }

        u->uri.len = last - uri;
        u->uri.data = uri;

        last = uri;

        if (uri < port) {
            port = NULL;
        }
    }

    if (port) {
        port++;

        len = last - port;

        if (u->listen) {
            dash = ngx_strlchr(port, last, '-');

            if (dash) {
                dash++;

                n = ngx_atoi(dash, last - dash);

                if (n < 1 || n > 65535) {
                    u->err = "invalid port";
                    return NGX_ERROR;
                }

                u->last_port = (in_port_t) n;

                len = dash - port - 1;
            }
        }

        n = ngx_atoi(port, len);

        if (n < 1 || n > 65535) {
            u->err = "invalid port";
            return NGX_ERROR;
        }

        if (u->last_port && n > u->last_port) {
            u->err = "invalid port range";
            return NGX_ERROR;
        }

        u->port = (in_port_t) n;
        sin->sin_port = htons((in_port_t) n);

        u->port_text.len = last - port;
        u->port_text.data = port;

        last = port - 1;

    } else {
        if (uri == NULL) {

            if (u->listen) {

                /* test value as port only */

                len = last - host;

                dash = ngx_strlchr(host, last, '-');

                if (dash) {
                    dash++;

                    n = ngx_atoi(dash, last - dash);

                    if (n == NGX_ERROR) {
                        goto no_port;
                    }

                    if (n < 1 || n > 65535) {
                        u->err = "invalid port";

                    } else {
                        u->last_port = (in_port_t) n;
                    }

                    len = dash - host - 1;
                }

                n = ngx_atoi(host, len);

                if (n != NGX_ERROR) {

                    if (u->err) {
                        return NGX_ERROR;
                    }

                    if (n < 1 || n > 65535) {
                        u->err = "invalid port";
                        return NGX_ERROR;
                    }

                    if (u->last_port && n > u->last_port) {
                        u->err = "invalid port range";
                        return NGX_ERROR;
                    }

                    u->port = (in_port_t) n;
                    sin->sin_port = htons((in_port_t) n);
                    sin->sin_addr.s_addr = INADDR_ANY;

                    u->port_text.len = last - host;
                    u->port_text.data = host;

                    u->wildcard = 1;

                    return ngx_inet_add_addr(pool, u, &u->sockaddr.sockaddr,
                                             u->socklen, 1);
                }
            }
        }

no_port:

        u->err = NULL;
        u->no_port = 1;
        u->port = u->default_port;
        sin->sin_port = htons(u->default_port);
        u->last_port = 0;
    }

    len = last - host;

    if (len == 0) {
        u->err = "no host";
        return NGX_ERROR;
    }

    u->host.len = len;
    u->host.data = host;

    if (u->listen && len == 1 && *host == '*') {
        sin->sin_addr.s_addr = INADDR_ANY;
        u->wildcard = 1;
        return ngx_inet_add_addr(pool, u, &u->sockaddr.sockaddr, u->socklen, 1);
    }

    sin->sin_addr.s_addr = ngx_inet_addr(host, len);

    if (sin->sin_addr.s_addr != INADDR_NONE) {

        if (sin->sin_addr.s_addr == INADDR_ANY) {
            u->wildcard = 1;
        }

        return ngx_inet_add_addr(pool, u, &u->sockaddr.sockaddr, u->socklen, 1);
    }

    if (u->no_resolve) {
        return NGX_OK;
    }

    if (ngx_inet_resolve_host(pool, u) != NGX_OK) {
        return NGX_ERROR;
    }

    u->family = u->addrs[0].sockaddr->sa_family;
    u->socklen = u->addrs[0].socklen;
    ngx_memcpy(&u->sockaddr, u->addrs[0].sockaddr, u->addrs[0].socklen);
    u->wildcard = ngx_inet_wildcard(&u->sockaddr.sockaddr);

    return NGX_OK;
}