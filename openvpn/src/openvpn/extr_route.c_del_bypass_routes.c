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
struct tuntap {int dummy; } ;
struct route_gateway_info {int dummy; } ;
struct route_bypass {int n_bypass; scalar_t__* bypass; } ;
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPV4_NETMASK_HOST ; 
 unsigned int ROUTE_REF_GW ; 
 int /*<<< orphan*/  del_route3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuntap const*,unsigned int,struct route_gateway_info const*,struct env_set const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
del_bypass_routes(struct route_bypass *rb,
                  in_addr_t gateway,
                  const struct tuntap *tt,
                  unsigned int flags,
                  const struct route_gateway_info *rgi,
                  const struct env_set *es,
                  openvpn_net_ctx_t *ctx)
{
    int i;
    for (i = 0; i < rb->n_bypass; ++i)
    {
        if (rb->bypass[i])
        {
            del_route3(rb->bypass[i],
                       IPV4_NETMASK_HOST,
                       gateway,
                       tt,
                       flags | ROUTE_REF_GW,
                       rgi,
                       es,
                       ctx);
        }
    }
}