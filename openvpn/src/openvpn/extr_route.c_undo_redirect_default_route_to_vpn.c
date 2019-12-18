#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tuntap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int flags; TYPE_2__ gateway; } ;
struct TYPE_6__ {int remote_host; int /*<<< orphan*/  remote_endpoint; int /*<<< orphan*/  bypass; } ;
struct route_list {int iflags; int flags; TYPE_3__ rgi; TYPE_1__ spec; } ;
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int IPV4_NETMASK_HOST ; 
 int RGI_ADDR_DEFINED ; 
 int RG_DEF1 ; 
 int RG_REROUTE_GW ; 
 int RL_DID_LOCAL ; 
 int RL_DID_REDIRECT_DEFAULT_GATEWAY ; 
 unsigned int ROUTE_REF_GW ; 
 int /*<<< orphan*/  add_route3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuntap const*,unsigned int,TYPE_3__*,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_bypass_routes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tuntap const*,unsigned int,TYPE_3__*,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_route3 (int,int,int /*<<< orphan*/ ,struct tuntap const*,unsigned int,TYPE_3__*,struct env_set const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
undo_redirect_default_route_to_vpn(struct route_list *rl,
                                   const struct tuntap *tt, unsigned int flags,
                                   const struct env_set *es,
                                   openvpn_net_ctx_t *ctx)
{
    if (rl && rl->iflags & RL_DID_REDIRECT_DEFAULT_GATEWAY)
    {
        /* delete remote host route */
        if (rl->iflags & RL_DID_LOCAL)
        {
            del_route3(rl->spec.remote_host,
                       IPV4_NETMASK_HOST,
                       rl->rgi.gateway.addr,
                       tt,
                       flags | ROUTE_REF_GW,
                       &rl->rgi,
                       es,
                       ctx);
            rl->iflags &= ~RL_DID_LOCAL;
        }

        /* delete special DHCP/DNS bypass route */
        del_bypass_routes(&rl->spec.bypass, rl->rgi.gateway.addr, tt, flags,
                          &rl->rgi, es, ctx);

        if (rl->flags & RG_REROUTE_GW)
        {
            if (rl->flags & RG_DEF1)
            {
                /* delete default route (1st component) */
                del_route3(0x00000000,
                           0x80000000,
                           rl->spec.remote_endpoint,
                           tt,
                           flags,
                           &rl->rgi,
                           es,
                           ctx);

                /* delete default route (2nd component) */
                del_route3(0x80000000,
                           0x80000000,
                           rl->spec.remote_endpoint,
                           tt,
                           flags,
                           &rl->rgi,
                           es,
                           ctx);
            }
            else
            {
                /* delete default route */
                del_route3(0,
                           0,
                           rl->spec.remote_endpoint,
                           tt,
                           flags,
                           &rl->rgi,
                           es,
                           ctx);
                /* restore original default route if there was any */
                if (rl->rgi.flags & RGI_ADDR_DEFINED)
                {
                    add_route3(0, 0, rl->rgi.gateway.addr, tt,
                               flags | ROUTE_REF_GW, &rl->rgi, es, ctx);
                }
            }
        }

        rl->iflags &= ~RL_DID_REDIRECT_DEFAULT_GATEWAY;
    }
}