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
struct TYPE_4__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct netpoll {int /*<<< orphan*/ * remote_mac; TYPE_2__ remote_ip; scalar_t__ ipv6; int /*<<< orphan*/ * remote_port; int /*<<< orphan*/ * dev_name; TYPE_1__ local_ip; int /*<<< orphan*/ * local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  np_info (struct netpoll*,char*,int /*<<< orphan*/ *) ; 

void netpoll_print_options(struct netpoll *np)
{
	np_info(np, "local port %d\n", np->local_port);
	if (np->ipv6)
		np_info(np, "local IPv6 address %pI6c\n", &np->local_ip.in6);
	else
		np_info(np, "local IPv4 address %pI4\n", &np->local_ip.ip);
	np_info(np, "interface '%s'\n", np->dev_name);
	np_info(np, "remote port %d\n", np->remote_port);
	if (np->ipv6)
		np_info(np, "remote IPv6 address %pI6c\n", &np->remote_ip.in6);
	else
		np_info(np, "remote IPv4 address %pI4\n", &np->remote_ip.ip);
	np_info(np, "remote ethernet address %pM\n", np->remote_mac);
}