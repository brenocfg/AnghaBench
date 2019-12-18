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
struct net {int /*<<< orphan*/  nfnl; } ;

/* Variables and functions */
 int netlink_has_listeners (int /*<<< orphan*/ ,unsigned int) ; 

int nfnetlink_has_listeners(struct net *net, unsigned int group)
{
	return netlink_has_listeners(net->nfnl, group);
}