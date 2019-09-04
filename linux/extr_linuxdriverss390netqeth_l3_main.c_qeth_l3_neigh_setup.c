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
struct net_device {int dummy; } ;
struct neigh_parms {int /*<<< orphan*/  neigh_setup; TYPE_1__* tbl; } ;
struct TYPE_2__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  qeth_l3_neigh_setup_noarp ; 

__attribute__((used)) static int
qeth_l3_neigh_setup(struct net_device *dev, struct neigh_parms *np)
{
	if (np->tbl->family == AF_INET)
		np->neigh_setup = qeth_l3_neigh_setup_noarp;

	return 0;
}