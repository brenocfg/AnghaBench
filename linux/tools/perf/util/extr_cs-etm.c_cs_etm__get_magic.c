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
typedef  int /*<<< orphan*/  u64 ;
struct int_node {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 size_t CS_ETM_MAGIC ; 
 int EINVAL ; 
 struct int_node* intlist__find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traceid_list ; 

__attribute__((used)) static int cs_etm__get_magic(u8 trace_chan_id, u64 *magic)
{
	struct int_node *inode;
	u64 *metadata;

	inode = intlist__find(traceid_list, trace_chan_id);
	if (!inode)
		return -EINVAL;

	metadata = inode->priv;
	*magic = metadata[CS_ETM_MAGIC];
	return 0;
}