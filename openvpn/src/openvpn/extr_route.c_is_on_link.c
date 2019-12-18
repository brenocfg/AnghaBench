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
struct route_gateway_info {int flags; } ;

/* Variables and functions */
 int const LR_MATCH ; 
 int RGI_ON_LINK ; 
 unsigned int const ROUTE_REF_GW ; 

__attribute__((used)) static inline bool
is_on_link(const int is_local_route, const unsigned int flags, const struct route_gateway_info *rgi)
{
    return rgi && (is_local_route == LR_MATCH || ((flags & ROUTE_REF_GW) && (rgi->flags & RGI_ON_LINK)));
}