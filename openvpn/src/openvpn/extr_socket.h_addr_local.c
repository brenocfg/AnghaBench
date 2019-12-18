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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
addr_local(const struct sockaddr *addr)
{
    if (!addr)
    {
        return false;
    }
    switch (addr->sa_family)
    {
        case AF_INET:
            return ((const struct sockaddr_in *)addr)->sin_addr.s_addr == htonl(INADDR_LOOPBACK);

        case AF_INET6:
            return IN6_IS_ADDR_LOOPBACK(&((const struct sockaddr_in6 *)addr)->sin6_addr);

        default:
            return false;
    }
}