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
struct TYPE_13__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {TYPE_2__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_15__ {int /*<<< orphan*/  rules; } ;
typedef  TYPE_5__ ngx_http_access_loc_conf_t ;
struct TYPE_12__ {TYPE_1__* sockaddr; } ;
struct TYPE_11__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  ngx_http_access_inet (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_access_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_access_handler(ngx_http_request_t *r)
{
    struct sockaddr_in          *sin;
    ngx_http_access_loc_conf_t  *alcf;
#if (NGX_HAVE_INET6)
    u_char                      *p;
    in_addr_t                    addr;
    struct sockaddr_in6         *sin6;
#endif

    alcf = ngx_http_get_module_loc_conf(r, ngx_http_access_module);

    switch (r->connection->sockaddr->sa_family) {

    case AF_INET:
        if (alcf->rules) {
            sin = (struct sockaddr_in *) r->connection->sockaddr;
            return ngx_http_access_inet(r, alcf, sin->sin_addr.s_addr);
        }
        break;

#if (NGX_HAVE_INET6)

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) r->connection->sockaddr;
        p = sin6->sin6_addr.s6_addr;

        if (alcf->rules && IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
            addr = p[12] << 24;
            addr += p[13] << 16;
            addr += p[14] << 8;
            addr += p[15];
            return ngx_http_access_inet(r, alcf, htonl(addr));
        }

        if (alcf->rules6) {
            return ngx_http_access_inet6(r, alcf, p);
        }

        break;

#endif

#if (NGX_HAVE_UNIX_DOMAIN)

    case AF_UNIX:
        if (alcf->rules_un) {
            return ngx_http_access_unix(r, alcf);
        }

        break;

#endif
    }

    return NGX_DECLINED;
}