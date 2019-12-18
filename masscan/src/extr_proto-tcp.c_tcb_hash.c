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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ syn_cookie (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
tcb_hash(   unsigned ip_me, unsigned port_me, 
            unsigned ip_them, unsigned port_them,
            uint64_t entropy)
{
    unsigned index;

    /* TCB hash table uses symmetric hash, so incoming/outgoing packets
     * get the same hash. */
    index = (unsigned)syn_cookie(   ip_me   ^ ip_them,
                                    port_me ^ port_them,
                                    ip_me   ^ ip_them,
                                    port_me ^ port_them,
                                    entropy
                                    );
    return index;
}