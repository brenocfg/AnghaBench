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
struct tuntap {int /*<<< orphan*/  actual_name; int /*<<< orphan*/  did_ifconfig_ipv6_setup; } ;
struct route_list {int iflags; int /*<<< orphan*/  rgi; struct route_ipv4* routes; } ;
struct route_ipv6_list {int iflags; struct route_ipv6* routes_ipv6; } ;
struct route_ipv6 {struct route_ipv6* next; } ;
struct route_ipv4 {int /*<<< orphan*/  netmask; int /*<<< orphan*/  network; struct route_ipv4* next; } ;
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  OPENVPN_STATE_ADD_ROUTES ; 
 int RL_ROUTES_ADDED ; 
 unsigned int ROUTE_DELETE_FIRST ; 
 int /*<<< orphan*/  add_route (struct route_ipv4*,struct tuntap const*,unsigned int,int /*<<< orphan*/ *,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_route_ipv6 (struct route_ipv6*,struct tuntap const*,unsigned int,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_subnet_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  delete_route (struct route_ipv4*,struct tuntap const*,unsigned int,int /*<<< orphan*/ *,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_route_ipv6 (struct route_ipv6*,struct tuntap const*,unsigned int,struct env_set const*,int /*<<< orphan*/ *) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_set_state (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirect_default_route_to_vpn (struct route_list*,struct tuntap const*,unsigned int,struct env_set const*,int /*<<< orphan*/ *) ; 

void
add_routes(struct route_list *rl, struct route_ipv6_list *rl6,
           const struct tuntap *tt, unsigned int flags,
           const struct env_set *es, openvpn_net_ctx_t *ctx)
{
    redirect_default_route_to_vpn(rl, tt, flags, es, ctx);
    if (rl && !(rl->iflags & RL_ROUTES_ADDED) )
    {
        struct route_ipv4 *r;

#ifdef ENABLE_MANAGEMENT
        if (management && rl->routes)
        {
            management_set_state(management,
                                 OPENVPN_STATE_ADD_ROUTES,
                                 NULL,
                                 NULL,
                                 NULL,
                                 NULL,
                                 NULL);
        }
#endif

        for (r = rl->routes; r; r = r->next)
        {
            check_subnet_conflict(r->network, r->netmask, "route");
            if (flags & ROUTE_DELETE_FIRST)
            {
                delete_route(r, tt, flags, &rl->rgi, es, ctx);
            }
            add_route(r, tt, flags, &rl->rgi, es, ctx);
        }
        rl->iflags |= RL_ROUTES_ADDED;
    }
    if (rl6 && !(rl6->iflags & RL_ROUTES_ADDED) )
    {
        struct route_ipv6 *r;

        if (!tt->did_ifconfig_ipv6_setup)
        {
            msg(M_INFO, "WARNING: OpenVPN was configured to add an IPv6 "
                "route over %s. However, no IPv6 has been configured for "
                "this interface, therefore the route installation may "
                "fail or may not work as expected.", tt->actual_name);
        }

        for (r = rl6->routes_ipv6; r; r = r->next)
        {
            if (flags & ROUTE_DELETE_FIRST)
            {
                delete_route_ipv6(r, tt, flags, es, ctx);
            }
            add_route_ipv6(r, tt, flags, es, ctx);
        }
        rl6->iflags |= RL_ROUTES_ADDED;
    }
}