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
struct ip6_tnl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6erspan_calc_hlen (struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6gre_tnl_link_config_common (struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6gre_tnl_link_config_route (struct ip6_tnl*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip6erspan_tnl_link_config(struct ip6_tnl *t, int set_mtu)
{
	ip6gre_tnl_link_config_common(t);
	ip6gre_tnl_link_config_route(t, set_mtu, ip6erspan_calc_hlen(t));
}