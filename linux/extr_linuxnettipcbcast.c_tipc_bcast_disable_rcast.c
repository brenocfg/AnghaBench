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
struct net {int dummy; } ;
struct TYPE_2__ {int rcast_support; } ;

/* Variables and functions */
 TYPE_1__* tipc_bc_base (struct net*) ; 

void tipc_bcast_disable_rcast(struct net *net)
{
	tipc_bc_base(net)->rcast_support = false;
}