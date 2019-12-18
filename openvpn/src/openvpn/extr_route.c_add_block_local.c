#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; scalar_t__ remote_host_local; int /*<<< orphan*/  remote_endpoint; int /*<<< orphan*/  bypass; } ;
struct route_gateway_address {int addr; int netmask; } ;
struct TYPE_3__ {int const flags; size_t n_addrs; struct route_gateway_address const gateway; struct route_gateway_address* addrs; } ;
struct route_list {int flags; TYPE_2__ spec; TYPE_1__ rgi; } ;

/* Variables and functions */
 int RGI_ADDR_DEFINED ; 
 int RGI_NETMASK_DEFINED ; 
 int RG_BLOCK_LOCAL ; 
 int RTSA_REMOTE_ENDPOINT ; 
 scalar_t__ TLA_LOCAL ; 
 int /*<<< orphan*/  add_block_local_item (struct route_list*,struct route_gateway_address const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_bypass_address (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_block_local(struct route_list *rl)
{
    const int rgi_needed = (RGI_ADDR_DEFINED|RGI_NETMASK_DEFINED);
    if ((rl->flags & RG_BLOCK_LOCAL)
        && (rl->rgi.flags & rgi_needed) == rgi_needed
        && (rl->spec.flags & RTSA_REMOTE_ENDPOINT)
        && rl->spec.remote_host_local != TLA_LOCAL)
    {
        size_t i;

#ifndef TARGET_ANDROID
        /* add bypass for gateway addr */
        add_bypass_address(&rl->spec.bypass, rl->rgi.gateway.addr);
#endif

        /* block access to local subnet */
        add_block_local_item(rl, &rl->rgi.gateway, rl->spec.remote_endpoint);

        /* process additional subnets on gateway interface */
        for (i = 0; i < rl->rgi.n_addrs; ++i)
        {
            const struct route_gateway_address *gwa = &rl->rgi.addrs[i];
            /* omit the add/subnet in &rl->rgi which we processed above */
            if (!((rl->rgi.gateway.addr & rl->rgi.gateway.netmask) == (gwa->addr & gwa->netmask)
                  && rl->rgi.gateway.netmask == gwa->netmask))
            {
                add_block_local_item(rl, gwa, rl->spec.remote_endpoint);
            }
        }
    }
}