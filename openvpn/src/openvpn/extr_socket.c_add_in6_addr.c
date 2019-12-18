#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct in6_addr {scalar_t__* s6_addr; } ;

/* Variables and functions */
 scalar_t__ UINT8_MAX ; 

struct in6_addr
add_in6_addr( struct in6_addr base, uint32_t add )
{
    int i;

    for (i = 15; i>=0 && add > 0; i--)
    {
        register int carry;
        register uint32_t h;

        h = (unsigned char) base.s6_addr[i];
        base.s6_addr[i] = (h+add) & UINT8_MAX;

        /* using explicit carry for the 8-bit additions will catch
         * 8-bit and(!) 32-bit overruns nicely
         */
        carry = ((h & 0xff)  + (add & 0xff)) >> 8;
        add = (add>>8) + carry;
    }
    return base;
}