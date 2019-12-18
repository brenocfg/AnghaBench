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
struct route_ipv6_gateway_info {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct route_ipv6_gateway_info) ; 
 int /*<<< orphan*/  D_ROUTE ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

void
get_default_gateway_ipv6(struct route_ipv6_gateway_info *rgi6,
                         const struct in6_addr *dest, openvpn_net_ctx_t *ctx)
{
    msg(D_ROUTE, "no support for get_default_gateway_ipv6() on this system");
    CLEAR(*rgi6);
}