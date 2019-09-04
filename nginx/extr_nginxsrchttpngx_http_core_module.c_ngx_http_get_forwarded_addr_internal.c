#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_7__ {int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_2__ ngx_addr_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_cidr_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_parse_addr_port (int /*<<< orphan*/ ,TYPE_2__*,char*,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_get_forwarded_addr_internal(ngx_http_request_t *r, ngx_addr_t *addr,
    u_char *xff, size_t xfflen, ngx_array_t *proxies, int recursive)
{
    u_char      *p;
    ngx_int_t    rc;
    ngx_addr_t   paddr;

    if (ngx_cidr_match(addr->sockaddr, proxies) != NGX_OK) {
        return NGX_DECLINED;
    }

    for (p = xff + xfflen - 1; p > xff; p--, xfflen--) {
        if (*p != ' ' && *p != ',') {
            break;
        }
    }

    for ( /* void */ ; p > xff; p--) {
        if (*p == ' ' || *p == ',') {
            p++;
            break;
        }
    }

    if (ngx_parse_addr_port(r->pool, &paddr, p, xfflen - (p - xff)) != NGX_OK) {
        return NGX_DECLINED;
    }

    *addr = paddr;

    if (recursive && p > xff) {
        rc = ngx_http_get_forwarded_addr_internal(r, addr, xff, p - 1 - xff,
                                                  proxies, 1);

        if (rc == NGX_DECLINED) {
            return NGX_DONE;
        }

        /* rc == NGX_OK || rc == NGX_DONE  */
        return rc;
    }

    return NGX_OK;
}