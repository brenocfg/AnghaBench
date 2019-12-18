#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_stream_geoip_conf_t ;
struct TYPE_11__ {TYPE_2__* sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_5__ ngx_addr_t ;
typedef  int in_addr_t ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  socklen; TYPE_2__* sockaddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int INADDR_NONE ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long
ngx_stream_geoip_addr(ngx_stream_session_t *s, ngx_stream_geoip_conf_t *gcf)
{
    ngx_addr_t           addr;
    struct sockaddr_in  *sin;

    addr.sockaddr = s->connection->sockaddr;
    addr.socklen = s->connection->socklen;
    /* addr.name = s->connection->addr_text; */

#if (NGX_HAVE_INET6)

    if (addr.sockaddr->sa_family == AF_INET6) {
        u_char           *p;
        in_addr_t         inaddr;
        struct in6_addr  *inaddr6;

        inaddr6 = &((struct sockaddr_in6 *) addr.sockaddr)->sin6_addr;

        if (IN6_IS_ADDR_V4MAPPED(inaddr6)) {
            p = inaddr6->s6_addr;

            inaddr = p[12] << 24;
            inaddr += p[13] << 16;
            inaddr += p[14] << 8;
            inaddr += p[15];

            return inaddr;
        }
    }

#endif

    if (addr.sockaddr->sa_family != AF_INET) {
        return INADDR_NONE;
    }

    sin = (struct sockaddr_in *) addr.sockaddr;
    return ntohl(sin->sin_addr.s_addr);
}