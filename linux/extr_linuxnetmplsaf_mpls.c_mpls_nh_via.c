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
typedef  int /*<<< orphan*/  u8 ;
struct mpls_route {int dummy; } ;
struct mpls_nh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* __mpls_nh_via (struct mpls_route*,struct mpls_nh*) ; 

__attribute__((used)) static const u8 *mpls_nh_via(const struct mpls_route *rt,
			     const struct mpls_nh *nh)
{
	return __mpls_nh_via((struct mpls_route *)rt, (struct mpls_nh *)nh);
}