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
struct tipc_bc_base {int bc_threshold; int rc_ratio; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 
 int /*<<< orphan*/  tipc_bc_sndlink (struct net*) ; 
 int tipc_link_bc_peers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_bcbase_calc_bc_threshold(struct net *net)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);
	int cluster_size = tipc_link_bc_peers(tipc_bc_sndlink(net));

	bb->bc_threshold = 1 + (cluster_size * bb->rc_ratio / 100);
}