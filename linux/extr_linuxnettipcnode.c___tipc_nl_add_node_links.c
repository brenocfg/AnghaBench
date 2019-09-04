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
struct tipc_nl_msg {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 size_t MAX_BEARERS ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int __tipc_nl_add_link (struct net*,struct tipc_nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tipc_nl_add_node_links(struct net *net, struct tipc_nl_msg *msg,
				    struct tipc_node *node, u32 *prev_link)
{
	u32 i;
	int err;

	for (i = *prev_link; i < MAX_BEARERS; i++) {
		*prev_link = i;

		if (!node->links[i].link)
			continue;

		err = __tipc_nl_add_link(net, msg,
					 node->links[i].link, NLM_F_MULTI);
		if (err)
			return err;
	}
	*prev_link = 0;

	return 0;
}