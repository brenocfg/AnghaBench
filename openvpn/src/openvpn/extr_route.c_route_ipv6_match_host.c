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
struct TYPE_2__ {unsigned int* s6_addr; } ;
struct route_ipv6 {unsigned int netbits; TYPE_1__ network; } ;
struct in6_addr {unsigned int* s6_addr; } ;

/* Variables and functions */

__attribute__((used)) static bool
route_ipv6_match_host( const struct route_ipv6 *r6,
                       const struct in6_addr *host )
{
    unsigned int bits = r6->netbits;
    int i;
    unsigned int mask;

    if (bits>128)
    {
        return false;
    }

    for (i = 0; bits >= 8; i++, bits -= 8)
    {
        if (r6->network.s6_addr[i] != host->s6_addr[i])
        {
            return false;
        }
    }

    if (bits == 0)
    {
        return true;
    }

    mask = 0xff << (8-bits);

    if ( (r6->network.s6_addr[i] & mask) == (host->s6_addr[i] & mask ))
    {
        return true;
    }

    return false;
}