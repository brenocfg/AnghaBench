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
struct tipc_net {int /*<<< orphan*/ * bearer_list; } ;
struct tipc_bearer {int identity; scalar_t__ disc; int /*<<< orphan*/  media_ptr; TYPE_1__* media; int /*<<< orphan*/  up; int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_media ) (struct tipc_bearer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct tipc_bearer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct tipc_bearer*) ; 
 int /*<<< orphan*/  tipc_disc_delete (scalar_t__) ; 
 int /*<<< orphan*/  tipc_mon_delete (struct net*,int) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_node_delete_links (struct net*,int) ; 

__attribute__((used)) static void bearer_disable(struct net *net, struct tipc_bearer *b)
{
	struct tipc_net *tn = tipc_net(net);
	int bearer_id = b->identity;

	pr_info("Disabling bearer <%s>\n", b->name);
	clear_bit_unlock(0, &b->up);
	tipc_node_delete_links(net, bearer_id);
	b->media->disable_media(b);
	RCU_INIT_POINTER(b->media_ptr, NULL);
	if (b->disc)
		tipc_disc_delete(b->disc);
	RCU_INIT_POINTER(tn->bearer_list[bearer_id], NULL);
	kfree_rcu(b, rcu);
	tipc_mon_delete(net, bearer_id);
}