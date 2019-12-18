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
typedef  void* u32 ;
struct tipc_member {int state; void* node; scalar_t__ bc_acked; void* instance; void* port; struct tipc_group* group; int /*<<< orphan*/  deferredq; int /*<<< orphan*/  small_win; int /*<<< orphan*/  list; } ;
struct tipc_group {int /*<<< orphan*/  dests; int /*<<< orphan*/  member_cnt; scalar_t__ bc_snd_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 struct tipc_member* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_add_to_tree (struct tipc_group*,struct tipc_member*) ; 
 int /*<<< orphan*/  tipc_nlist_add (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static struct tipc_member *tipc_group_create_member(struct tipc_group *grp,
						    u32 node, u32 port,
						    u32 instance, int state)
{
	struct tipc_member *m;

	m = kzalloc(sizeof(*m), GFP_ATOMIC);
	if (!m)
		return NULL;
	INIT_LIST_HEAD(&m->list);
	INIT_LIST_HEAD(&m->small_win);
	__skb_queue_head_init(&m->deferredq);
	m->group = grp;
	m->node = node;
	m->port = port;
	m->instance = instance;
	m->bc_acked = grp->bc_snd_nxt - 1;
	grp->member_cnt++;
	tipc_group_add_to_tree(grp, m);
	tipc_nlist_add(&grp->dests, m->node);
	m->state = state;
	return m;
}