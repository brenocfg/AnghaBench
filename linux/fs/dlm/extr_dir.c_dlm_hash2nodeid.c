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
typedef  int uint32_t ;
struct dlm_ls {int ls_num_nodes; int ls_total_weight; int* ls_node_array; } ;

/* Variables and functions */
 int dlm_our_nodeid () ; 

int dlm_hash2nodeid(struct dlm_ls *ls, uint32_t hash)
{
	uint32_t node;

	if (ls->ls_num_nodes == 1)
		return dlm_our_nodeid();
	else {
		node = (hash >> 16) % ls->ls_total_weight;
		return ls->ls_node_array[node];
	}
}