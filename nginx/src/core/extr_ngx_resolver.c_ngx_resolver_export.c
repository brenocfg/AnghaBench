#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_4__ sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;
typedef  int ngx_uint_t ;
struct TYPE_15__ {struct sockaddr_in6 sockaddr_in6; struct sockaddr_in sockaddr_in; } ;
typedef  TYPE_5__ ngx_sockaddr_t ;
typedef  int /*<<< orphan*/  ngx_resolver_t ;
struct TYPE_13__ {struct in6_addr* addrs6; struct in6_addr addr6; } ;
struct TYPE_11__ {int /*<<< orphan*/ * addrs; int /*<<< orphan*/  addr; } ;
struct TYPE_16__ {int naddrs; int naddrs6; TYPE_3__ u6; TYPE_1__ u; } ;
typedef  TYPE_6__ ngx_resolver_node_t ;
struct TYPE_17__ {int socklen; struct sockaddr* sockaddr; } ;
typedef  TYPE_7__ ngx_resolver_addr_t ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ngx_random () ; 
 void* ngx_resolver_calloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_resolver_free (int /*<<< orphan*/ *,TYPE_7__*) ; 

__attribute__((used)) static ngx_resolver_addr_t *
ngx_resolver_export(ngx_resolver_t *r, ngx_resolver_node_t *rn,
    ngx_uint_t rotate)
{
    ngx_uint_t            d, i, j, n;
    in_addr_t            *addr;
    ngx_sockaddr_t       *sockaddr;
    struct sockaddr_in   *sin;
    ngx_resolver_addr_t  *dst;
#if (NGX_HAVE_INET6)
    struct in6_addr      *addr6;
    struct sockaddr_in6  *sin6;
#endif

    n = rn->naddrs;
#if (NGX_HAVE_INET6)
    n += rn->naddrs6;
#endif

    dst = ngx_resolver_calloc(r, n * sizeof(ngx_resolver_addr_t));
    if (dst == NULL) {
        return NULL;
    }

    sockaddr = ngx_resolver_calloc(r, n * sizeof(ngx_sockaddr_t));
    if (sockaddr == NULL) {
        ngx_resolver_free(r, dst);
        return NULL;
    }

    i = 0;
    d = rotate ? ngx_random() % n : 0;

    if (rn->naddrs) {
        j = rotate ? ngx_random() % rn->naddrs : 0;

        addr = (rn->naddrs == 1) ? &rn->u.addr : rn->u.addrs;

        do {
            sin = &sockaddr[d].sockaddr_in;
            sin->sin_family = AF_INET;
            sin->sin_addr.s_addr = addr[j++];
            dst[d].sockaddr = (struct sockaddr *) sin;
            dst[d++].socklen = sizeof(struct sockaddr_in);

            if (d == n) {
                d = 0;
            }

            if (j == (ngx_uint_t) rn->naddrs) {
                j = 0;
            }
        } while (++i < (ngx_uint_t) rn->naddrs);
    }

#if (NGX_HAVE_INET6)
    if (rn->naddrs6) {
        j = rotate ? ngx_random() % rn->naddrs6 : 0;

        addr6 = (rn->naddrs6 == 1) ? &rn->u6.addr6 : rn->u6.addrs6;

        do {
            sin6 = &sockaddr[d].sockaddr_in6;
            sin6->sin6_family = AF_INET6;
            ngx_memcpy(sin6->sin6_addr.s6_addr, addr6[j++].s6_addr, 16);
            dst[d].sockaddr = (struct sockaddr *) sin6;
            dst[d++].socklen = sizeof(struct sockaddr_in6);

            if (d == n) {
                d = 0;
            }

            if (j == rn->naddrs6) {
                j = 0;
            }
        } while (++i < n);
    }
#endif

    return dst;
}