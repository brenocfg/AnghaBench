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
struct TYPE_2__ {scalar_t__ addr; scalar_t__ netmask; } ;
struct route_gateway_info {int const flags; size_t n_addrs; struct route_gateway_address* addrs; TYPE_1__ gateway; } ;
struct route_gateway_address {scalar_t__ addr; scalar_t__ netmask; } ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 int LR_MATCH ; 
 int LR_NOMATCH ; 
 int RGI_ADDR_DEFINED ; 
 int RGI_IFACE_DEFINED ; 
 int RGI_NETMASK_DEFINED ; 

__attribute__((used)) static int
local_route(in_addr_t network,
            in_addr_t netmask,
            in_addr_t gateway,
            const struct route_gateway_info *rgi)
{
    /* set LR_MATCH on local host routes */
    const int rgi_needed = (RGI_ADDR_DEFINED|RGI_NETMASK_DEFINED|RGI_IFACE_DEFINED);
    if (rgi
        && (rgi->flags & rgi_needed) == rgi_needed
        && gateway == rgi->gateway.addr
        && netmask == 0xFFFFFFFF)
    {
        if (((network ^  rgi->gateway.addr) & rgi->gateway.netmask) == 0)
        {
            return LR_MATCH;
        }
        else
        {
            /* examine additional subnets on gateway interface */
            size_t i;
            for (i = 0; i < rgi->n_addrs; ++i)
            {
                const struct route_gateway_address *gwa = &rgi->addrs[i];
                if (((network ^ gwa->addr) & gwa->netmask) == 0)
                {
                    return LR_MATCH;
                }
            }
        }
    }
    return LR_NOMATCH;
}