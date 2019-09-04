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
struct tipc_dest {int /*<<< orphan*/  list; void* port; void* node; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct tipc_dest* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ tipc_dest_find (struct list_head*,void*,void*) ; 
 scalar_t__ unlikely (int) ; 

bool tipc_dest_push(struct list_head *l, u32 node, u32 port)
{
	struct tipc_dest *dst;

	if (tipc_dest_find(l, node, port))
		return false;

	dst = kmalloc(sizeof(*dst), GFP_ATOMIC);
	if (unlikely(!dst))
		return false;
	dst->node = node;
	dst->port = port;
	list_add(&dst->list, l);
	return true;
}