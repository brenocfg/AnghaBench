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
struct TYPE_2__ {int addr; int netmask; } ;
struct route_gateway_info {int const flags; TYPE_1__ gateway; } ;
struct gc_arena {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WARN ; 
 int RGI_ADDR_DEFINED ; 
 int RGI_NETMASK_DEFINED ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  get_default_gateway (struct route_gateway_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

void
warn_on_use_of_common_subnets(openvpn_net_ctx_t *ctx)
{
    struct gc_arena gc = gc_new();
    struct route_gateway_info rgi;
    const int needed = (RGI_ADDR_DEFINED|RGI_NETMASK_DEFINED);

    get_default_gateway(&rgi, ctx);
    if ((rgi.flags & needed) == needed)
    {
        const in_addr_t lan_network = rgi.gateway.addr & rgi.gateway.netmask;
        if (lan_network == 0xC0A80000 || lan_network == 0xC0A80100)
        {
            msg(M_WARN, "NOTE: your local LAN uses the extremely common subnet address 192.168.0.x or 192.168.1.x.  Be aware that this might create routing conflicts if you connect to the VPN server from public locations such as internet cafes that use the same subnet.");
        }
    }
    gc_free(&gc);
}