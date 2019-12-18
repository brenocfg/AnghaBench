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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct route_gateway_info {TYPE_1__ gateway; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int TLA_LOCAL ; 
 int TLA_NONLOCAL ; 
 int TLA_NOT_IMPLEMENTED ; 
 scalar_t__ local_route (int /*<<< orphan*/  const,int,int /*<<< orphan*/ ,struct route_gateway_info const*) ; 

int
test_local_addr(const in_addr_t addr, const struct route_gateway_info *rgi)  /* PLATFORM-SPECIFIC */
{
    if (rgi)
    {
        if (local_route(addr, 0xFFFFFFFF, rgi->gateway.addr, rgi))
        {
            return TLA_LOCAL;
        }
        else
        {
            return TLA_NONLOCAL;
        }
    }
    return TLA_NOT_IMPLEMENTED;
}