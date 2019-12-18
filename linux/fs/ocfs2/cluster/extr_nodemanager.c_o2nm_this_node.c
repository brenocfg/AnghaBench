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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cl_local_node; scalar_t__ cl_has_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 TYPE_1__* o2nm_single_cluster ; 

u8 o2nm_this_node(void)
{
	u8 node_num = O2NM_MAX_NODES;

	if (o2nm_single_cluster && o2nm_single_cluster->cl_has_local)
		node_num = o2nm_single_cluster->cl_local_node;

	return node_num;
}