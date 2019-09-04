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
struct dlm_recover {int nodes_count; struct dlm_config_node* nodes; } ;
struct dlm_config_node {int nodeid; } ;

/* Variables and functions */

__attribute__((used)) static struct dlm_config_node *find_config_node(struct dlm_recover *rv,
						int nodeid)
{
	int i;

	for (i = 0; i < rv->nodes_count; i++) {
		if (rv->nodes[i].nodeid == nodeid)
			return &rv->nodes[i];
	}
	return NULL;
}