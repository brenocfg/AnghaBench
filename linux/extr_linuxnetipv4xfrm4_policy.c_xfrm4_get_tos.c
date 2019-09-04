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
struct TYPE_3__ {int flowi4_tos; } ;
struct TYPE_4__ {TYPE_1__ ip4; } ;
struct flowi {TYPE_2__ u; } ;

/* Variables and functions */
 int IPTOS_RT_MASK ; 

__attribute__((used)) static int xfrm4_get_tos(const struct flowi *fl)
{
	return IPTOS_RT_MASK & fl->u.ip4.flowi4_tos; /* Strip ECN bits */
}