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
typedef  size_t u32 ;
struct tipc_node {TYPE_1__* links; } ;
struct tipc_link {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct tipc_link* link; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_BEARERS ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tipc_link_name (struct tipc_link*) ; 
 struct tipc_node* tipc_node_find (struct net*,size_t) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_unlock (struct tipc_node*) ; 

int tipc_node_get_linkname(struct net *net, u32 bearer_id, u32 addr,
			   char *linkname, size_t len)
{
	struct tipc_link *link;
	int err = -EINVAL;
	struct tipc_node *node = tipc_node_find(net, addr);

	if (!node)
		return err;

	if (bearer_id >= MAX_BEARERS)
		goto exit;

	tipc_node_read_lock(node);
	link = node->links[bearer_id].link;
	if (link) {
		strncpy(linkname, tipc_link_name(link), len);
		err = 0;
	}
	tipc_node_read_unlock(node);
exit:
	tipc_node_put(node);
	return err;
}