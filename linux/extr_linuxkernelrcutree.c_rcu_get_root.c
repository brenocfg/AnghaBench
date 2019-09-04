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
struct rcu_state {struct rcu_node* node; } ;
struct rcu_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct rcu_node *rcu_get_root(struct rcu_state *rsp)
{
	return &rsp->node[0];
}