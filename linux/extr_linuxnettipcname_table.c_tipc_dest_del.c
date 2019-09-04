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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_dest {int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tipc_dest*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct tipc_dest* tipc_dest_find (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool tipc_dest_del(struct list_head *l, u32 node, u32 port)
{
	struct tipc_dest *dst;

	dst = tipc_dest_find(l, node, port);
	if (!dst)
		return false;
	list_del(&dst->list);
	kfree(dst);
	return true;
}