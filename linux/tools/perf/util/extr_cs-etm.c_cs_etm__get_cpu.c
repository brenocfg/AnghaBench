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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct int_node {scalar_t__* priv; } ;

/* Variables and functions */
 size_t CS_ETM_CPU ; 
 int EINVAL ; 
 struct int_node* intlist__find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traceid_list ; 

int cs_etm__get_cpu(u8 trace_chan_id, int *cpu)
{
	struct int_node *inode;
	u64 *metadata;

	inode = intlist__find(traceid_list, trace_chan_id);
	if (!inode)
		return -EINVAL;

	metadata = inode->priv;
	*cpu = (int)metadata[CS_ETM_CPU];
	return 0;
}