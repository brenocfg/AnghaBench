#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_6__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct TYPE_7__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {size_t socklen; TYPE_4__* sockaddr; } ;
typedef  TYPE_3__ ngx_addr_t ;
typedef  scalar_t__ in_addr_t ;
struct TYPE_9__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 int AF_INET ; 
#define  AF_INET6 128 
 scalar_t__ INADDR_NONE ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_inet6_addr (scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_inet_addr (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_memzero (struct in6_addr*,int) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ *,size_t) ; 

ngx_int_t
ngx_parse_addr(ngx_pool_t *pool, ngx_addr_t *addr, u_char *text, size_t len)
{
    in_addr_t             inaddr;
    ngx_uint_t            family;
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct in6_addr       inaddr6;
    struct sockaddr_in6  *sin6;

    /*
     * prevent MSVC8 warning:
     *    potentially uninitialized local variable 'inaddr6' used
     */
    ngx_memzero(&inaddr6, sizeof(struct in6_addr));
#endif

    inaddr = ngx_inet_addr(text, len);

    if (inaddr != INADDR_NONE) {
        family = AF_INET;
        len = sizeof(struct sockaddr_in);

#if (NGX_HAVE_INET6)
    } else if (ngx_inet6_addr(text, len, inaddr6.s6_addr) == NGX_OK) {
        family = AF_INET6;
        len = sizeof(struct sockaddr_in6);

#endif
    } else {
        return NGX_DECLINED;
    }

    addr->sockaddr = ngx_pcalloc(pool, len);
    if (addr->sockaddr == NULL) {
        return NGX_ERROR;
    }

    addr->sockaddr->sa_family = (u_char) family;
    addr->socklen = len;

    switch (family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) addr->sockaddr;
        ngx_memcpy(sin6->sin6_addr.s6_addr, inaddr6.s6_addr, 16);
        break;
#endif

    default: /* AF_INET */
        sin = (struct sockaddr_in *) addr->sockaddr;
        sin->sin_addr.s_addr = inaddr;
        break;
    }

    return NGX_OK;
}