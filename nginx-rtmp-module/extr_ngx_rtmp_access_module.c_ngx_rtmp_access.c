#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_14__ {int* s6_addr; } ;
struct sockaddr_in6 {TYPE_9__ sin6_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_13__ {TYPE_3__* connection; } ;
typedef  TYPE_4__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_access_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int in_addr_t ;
struct TYPE_12__ {TYPE_2__* sockaddr; int /*<<< orphan*/  log; } ;
struct TYPE_11__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (TYPE_9__*) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_access_inet (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_access_inet6 (TYPE_4__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_access_module ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_app_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_access(ngx_rtmp_session_t *s, ngx_uint_t flag)
{
    struct sockaddr_in             *sin;
    ngx_rtmp_access_app_conf_t     *ascf;
#if (NGX_HAVE_INET6)
    u_char                         *p;
    in_addr_t                       addr;
    struct sockaddr_in6            *sin6;
#endif

    ascf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_access_module);
    if (ascf == NULL) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, s->connection->log, 0,
                       "access: NULL app conf");
        return NGX_ERROR;
    }

    /* relay etc */
    if (s->connection->sockaddr == NULL) {
        return NGX_OK;
    }

    switch (s->connection->sockaddr->sa_family) {

    case AF_INET:
        sin = (struct sockaddr_in *) s->connection->sockaddr;
        return ngx_rtmp_access_inet(s, sin->sin_addr.s_addr, flag);

#if (NGX_HAVE_INET6)

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) s->connection->sockaddr;
        p = sin6->sin6_addr.s6_addr;

        if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
            addr  = p[12] << 24;
            addr += p[13] << 16;
            addr += p[14] << 8;
            addr += p[15];
            return ngx_rtmp_access_inet(s, htonl(addr), flag);
        }

        return ngx_rtmp_access_inet6(s, p, flag);

#endif
    }

    return NGX_OK;
}