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
struct tipc_net {int /*<<< orphan*/ * node_id; int /*<<< orphan*/  node_id_string; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 

__attribute__((used)) static inline u8 *tipc_own_id(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);

	if (!strlen(tn->node_id_string))
		return NULL;
	return tn->node_id;
}