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
struct net_device {int dummy; } ;
struct dsa_switch_tree {struct dsa_port* cpu_dp; } ;
struct dsa_port {struct net_device* master; } ;

/* Variables and functions */
 void dsa_master_teardown (struct net_device*) ; 

__attribute__((used)) static void dsa_tree_teardown_master(struct dsa_switch_tree *dst)
{
	struct dsa_port *cpu_dp = dst->cpu_dp;
	struct net_device *master = cpu_dp->master;

	return dsa_master_teardown(master);
}