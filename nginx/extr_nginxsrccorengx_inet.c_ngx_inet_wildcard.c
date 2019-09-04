#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int ngx_uint_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  INADDR_ANY ; 

ngx_uint_t
ngx_inet_wildcard(struct sockaddr *sa)
{
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif

    switch (sa->sa_family) {

    case AF_INET:
        sin = (struct sockaddr_in *) sa;

        if (sin->sin_addr.s_addr == INADDR_ANY) {
            return 1;
        }

        break;

#if (NGX_HAVE_INET6)

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) sa;

        if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr)) {
            return 1;
        }

        break;

#endif
    }

    return 0;
}