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
typedef  int /*<<< orphan*/  u16 ;
struct list_head {int dummy; } ;
struct hsr_node {unsigned long* time_in; int /*<<< orphan*/  mac_list; int /*<<< orphan*/ * seq_out; int /*<<< orphan*/  macaddress_A; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HSR_PT_PORTS ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned long jiffies ; 
 struct hsr_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,struct list_head*) ; 

struct hsr_node *hsr_add_node(struct list_head *node_db, unsigned char addr[],
			      u16 seq_out)
{
	struct hsr_node *node;
	unsigned long now;
	int i;

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		return NULL;

	ether_addr_copy(node->macaddress_A, addr);

	/* We are only interested in time diffs here, so use current jiffies
	 * as initialization. (0 could trigger an spurious ring error warning).
	 */
	now = jiffies;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->time_in[i] = now;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->seq_out[i] = seq_out;

	list_add_tail_rcu(&node->mac_list, node_db);

	return node;
}