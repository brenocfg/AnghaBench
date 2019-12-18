#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_7__ {int last_port; int port; int /*<<< orphan*/  naddrs; TYPE_3__* addrs; } ;
typedef  TYPE_2__ ngx_url_t ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ name; int /*<<< orphan*/  socklen; struct sockaddr* sockaddr; } ;
typedef  TYPE_3__ ngx_addr_t ;

/* Variables and functions */
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_inet_set_port (struct sockaddr*,int) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ *,int) ; 
 struct sockaddr* ngx_pcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ *,size_t) ; 
 size_t ngx_sock_ntop (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static ngx_int_t
ngx_inet_add_addr(ngx_pool_t *pool, ngx_url_t *u, struct sockaddr *sockaddr,
    socklen_t socklen, ngx_uint_t total)
{
    u_char           *p;
    size_t            len;
    ngx_uint_t        i, nports;
    ngx_addr_t       *addr;
    struct sockaddr  *sa;

    nports = u->last_port ? u->last_port - u->port + 1 : 1;

    if (u->addrs == NULL) {
        u->addrs = ngx_palloc(pool, total * nports * sizeof(ngx_addr_t));
        if (u->addrs == NULL) {
            return NGX_ERROR;
        }
    }

    for (i = 0; i < nports; i++) {
        sa = ngx_pcalloc(pool, socklen);
        if (sa == NULL) {
            return NGX_ERROR;
        }

        ngx_memcpy(sa, sockaddr, socklen);

        ngx_inet_set_port(sa, u->port + i);

        switch (sa->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            len = NGX_INET6_ADDRSTRLEN + sizeof("[]:65536") - 1;
            break;
#endif

        default: /* AF_INET */
            len = NGX_INET_ADDRSTRLEN + sizeof(":65535") - 1;
        }

        p = ngx_pnalloc(pool, len);
        if (p == NULL) {
            return NGX_ERROR;
        }

        len = ngx_sock_ntop(sa, socklen, p, len, 1);

        addr = &u->addrs[u->naddrs++];

        addr->sockaddr = sa;
        addr->socklen = socklen;

        addr->name.len = len;
        addr->name.data = p;
    }

    return NGX_OK;
}