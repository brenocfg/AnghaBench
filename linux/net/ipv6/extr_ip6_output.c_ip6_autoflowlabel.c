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
struct net {int dummy; } ;
struct ipv6_pinfo {int autoflowlabel; int /*<<< orphan*/  autoflowlabel_set; } ;

/* Variables and functions */
 int ip6_default_np_autolabel (struct net*) ; 

bool ip6_autoflowlabel(struct net *net, const struct ipv6_pinfo *np)
{
	if (!np->autoflowlabel_set)
		return ip6_default_np_autolabel(net);
	else
		return np->autoflowlabel;
}