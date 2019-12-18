#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_2__ sin_addr; } ;
struct TYPE_6__ {int sa_family; } ;
struct TYPE_10__ {TYPE_4__ in6; TYPE_3__ in4; TYPE_1__ sa; } ;
struct openvpn_sockaddr {TYPE_5__ addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
addr_match(const struct openvpn_sockaddr *a1, const struct openvpn_sockaddr *a2)
{
    switch (a1->addr.sa.sa_family)
    {
        case AF_INET:
            return a1->addr.in4.sin_addr.s_addr == a2->addr.in4.sin_addr.s_addr;

        case AF_INET6:
            return IN6_ARE_ADDR_EQUAL(&a1->addr.in6.sin6_addr, &a2->addr.in6.sin6_addr);
    }
    ASSERT(0);
    return false;
}