#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ipi6_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; TYPE_4__ ipi_spec_dst; } ;
struct TYPE_14__ {TYPE_6__ in6; TYPE_5__ in4; } ;
struct TYPE_8__ {int sa_family; } ;
struct TYPE_9__ {TYPE_1__ sa; } ;
struct TYPE_10__ {TYPE_2__ addr; } ;
struct link_socket_actual {TYPE_7__ pi; TYPE_3__ dest; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
addr_defined_ipi(const struct link_socket_actual *lsa)
{
#if ENABLE_IP_PKTINFO
    if (!lsa)
    {
        return 0;
    }
    switch (lsa->dest.addr.sa.sa_family)
    {
#if defined(HAVE_IN_PKTINFO) && defined(HAVE_IPI_SPEC_DST)
        case AF_INET: return lsa->pi.in4.ipi_spec_dst.s_addr != 0;

#elif defined(IP_RECVDSTADDR)
        case AF_INET: return lsa->pi.in4.s_addr != 0;

#endif
        case AF_INET6: return !IN6_IS_ADDR_UNSPECIFIED(&lsa->pi.in6.ipi6_addr);

        default: return 0;
    }
#else  /* if ENABLE_IP_PKTINFO */
    ASSERT(0);
#endif
    return false;
}