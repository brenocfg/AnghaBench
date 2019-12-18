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
struct ipt_clusterip_tgt_info {int num_local_nodes; scalar_t__* local_nodes; } ;
struct clusterip_config {int /*<<< orphan*/  local_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clusterip_config_init_nodelist(struct clusterip_config *c,
			       const struct ipt_clusterip_tgt_info *i)
{
	int n;

	for (n = 0; n < i->num_local_nodes; n++)
		set_bit(i->local_nodes[n] - 1, &c->local_nodes);
}