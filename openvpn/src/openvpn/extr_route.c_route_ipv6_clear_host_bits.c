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
struct TYPE_2__ {int* s6_addr; } ;
struct route_ipv6 {int netbits; TYPE_1__ network; } ;

/* Variables and functions */

void
route_ipv6_clear_host_bits( struct route_ipv6 *r6 )
{
    /* clear host bit parts of route
     * (needed if routes are specified improperly, or if we need to
     * explicitly setup/clear the "connected" network routes on some OSes)
     */
    int byte = 15;
    int bits_to_clear = 128 - r6->netbits;

    while (byte >= 0 && bits_to_clear > 0)
    {
        if (bits_to_clear >= 8)
        {
            r6->network.s6_addr[byte--] = 0; bits_to_clear -= 8;
        }
        else
        {
            r6->network.s6_addr[byte--] &= (0xff << bits_to_clear); bits_to_clear = 0;
        }
    }
}